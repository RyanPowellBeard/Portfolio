#include "addinvoicedialog.h"
#include "ui_addinvoicedialog.h"
#include "DatabaseManager.h"
#include "invoicedao.h"
#include "clientdao.h"
#include "customercard.h"

#include <QMessageBox>
#include <QDate>
#include <QCompleter>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QSignalBlocker>

namespace {
// Index in NetTerms_ComboBox -> days until due. Kept in one place so the
// combo box population order and this lookup can't drift apart silently.
const int kNetTermsDays[] = {0, 15, 30, 45, 60};
const int kDefaultNetTermsIndex = 2; // "Net 30"
}

AddInvoiceDialog::AddInvoiceDialog(DatabaseManager& dbManager, int preselectedClientId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddInvoiceDialog)
    , m_dbManager(dbManager) // Bind reference in initializer list
{
    ui->setupUi(this);

    populateClientCompleter(preselectedClientId);

    // Live-refresh the client summary panel whenever the typed client
    // resolves to a real client, whether via picking a completer entry or
    // tabbing away after typing an exact match.
    connect(ui->Client_LineEdit->completer(), QOverload<const QString &>::of(&QCompleter::activated),
            this, [this](const QString &) { onClientSelectionChanged(); });
    connect(ui->Client_LineEdit, &QLineEdit::editingFinished, this, &AddInvoiceDialog::onClientSelectionChanged);
    onClientSelectionChanged(); // picks up the preselected client, if any

    // Net Terms recomputes Due Date from the current Issue Date. Manual
    // edits to Due Date afterward stick until Net Terms is changed again.
    connect(ui->NetTerms_ComboBox, &QComboBox::currentIndexChanged, this, [this](int index) {
        constexpr int kCount = sizeof(kNetTermsDays) / sizeof(kNetTermsDays[0]);
        if (index >= 0 && index < kCount) {
            ui->DueDate_DateEdit->setDate(ui->IssueDate_DateEdit->date().addDays(kNetTermsDays[index]));
        }
    });

    // TOTAL (per row) and taxTotal_lineEdit/GrandTotal_lineEdit (invoice-wide)
    // are all derived from QUANTITY, AMOUNT, and TAX, so any edit to those
    // needs to ripple through.
    connect(ui->Items_TableWidget, &QTableWidget::cellChanged, this, &AddInvoiceDialog::onItemsTableCellChanged);

    // Sensible defaults for a brand-new invoice
    ui->IssueDate_DateEdit->setDate(QDate::currentDate());
    ui->NetTerms_ComboBox->setCurrentIndex(kDefaultNetTermsIndex); // also sets Due Date via the connection above

    ui->Client_LineEdit->setPlaceholderText("Type client name...");
    ui->InvoiceNumber_LineEdit->setPlaceholderText("Invoice Number");
    ui->PONumber_LineEdit->setPlaceholderText("PO Number");
    ui->Notes_PlainTextEdit->setPlaceholderText("Notes");
}

AddInvoiceDialog::~AddInvoiceDialog()
{
    delete ui;
}

void AddInvoiceDialog::populateClientCompleter(int preselectedClientId)
{
    m_clientDisplayNameToId.clear();

    // Empty search term matches every client (LIKE '%%')
    ClientDao clientDao(m_dbManager);
    QVector<Client> clients = clientDao.searchClients(QString());

    QStringList displayNames;
    QString preselectedDisplayName;

    for (const Client &client : clients) {
        QString display = QString("%1 %2").arg(client.firstName, client.lastName).trimmed();
        if (!client.businessName.isEmpty()) {
            display += QString(" (%1)").arg(client.businessName);
        }

        // Note: if two clients share an identical display name, the later
        // one wins the id lookup below. Good enough for a typeahead field;
        // revisit if that collision turns out to matter in practice.
        m_clientDisplayNameToId.insert(display, client.id);
        displayNames << display;

        if (preselectedClientId != 0 && client.id == preselectedClientId) {
            preselectedDisplayName = display;
        }
    }

    QCompleter *completer = new QCompleter(displayNames, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setFilterMode(Qt::MatchContains); // matches anywhere in the name, not just the start
    completer->setCompletionMode(QCompleter::PopupCompletion); // live dropdown as you type
    ui->Client_LineEdit->setCompleter(completer);

    if (!preselectedDisplayName.isEmpty()) {
        ui->Client_LineEdit->setText(preselectedDisplayName);
    }
}

int AddInvoiceDialog::resolveSelectedClientId() const
{
    return m_clientDisplayNameToId.value(ui->Client_LineEdit->text().trimmed(), 0);
}

void AddInvoiceDialog::onClientSelectionChanged()
{
    refreshClientSummary(resolveSelectedClientId());
}

void AddInvoiceDialog::refreshClientSummary(int clientId)
{
    if (clientId == 0) {
        ui->ClientSummary_TextBrowser->clear();
        return;
    }

    ClientDao clientDao(m_dbManager);
    Client client = clientDao.getClientById(clientId);
    if (client.id == 0) {
        ui->ClientSummary_TextBrowser->clear();
        return;
    }

    QStringList lines;
    QString name = QString("%1 %2").arg(client.firstName, client.lastName).trimmed();
    lines << name;
    if (!client.businessName.isEmpty()) {
        lines << client.businessName;
    }
    if (!client.email.isEmpty()) {
        lines << client.email;
    }
    if (!client.phoneNumber.isEmpty()) {
        lines << client.phoneNumber;
    }
    if (!client.address1.isEmpty()) {
        lines << client.address1;
    }
    if (!client.address2.isEmpty()) {
        lines << client.address2;
    }
    QString cityStateZip = QString("%1%2%3")
        .arg(client.city, client.state.isEmpty() ? "" : ", " + client.state, client.postalCode.isEmpty() ? "" : " " + client.postalCode);
    if (!cityStateZip.trimmed().isEmpty()) {
        lines << cityStateZip;
    }

    ui->ClientSummary_TextBrowser->setPlainText(lines.join("\n"));
}

void AddInvoiceDialog::on_EditCustomer_PushButton_clicked()
{
    int clientId = resolveSelectedClientId();
    if (clientId == 0) {
        QMessageBox::warning(this, "No Client Selected", "Please select a client from the dropdown first.");
        return;
    }

    CustomerCard *card = new CustomerCard(m_dbManager, clientId, this);

    // If the name/business changes, the completer list and summary need to
    // catch up so this dialog isn't showing stale client info.
    connect(card, &CustomerCard::customerUpdated, this, [this](int updatedClientId) {
        populateClientCompleter(updatedClientId);
        refreshClientSummary(updatedClientId);
    });

    card->show();
    card->raise();
    card->activateWindow();
}

void AddInvoiceDialog::on_AddItem_PushButton_clicked()
{
    addBlankItemRow();
}

void AddInvoiceDialog::addBlankItemRow()
{
    int row = ui->Items_TableWidget->rowCount();

    // Setting these items fires cellChanged for each one, and TOTAL isn't
    // in place yet while ITEM/QUANTITY/DESCRIPTION/AMOUNT are being added.
    // Block signals for the initial population and recalc once at the end
    // instead of reacting to every intermediate setItem call.
    const QSignalBlocker blocker(ui->Items_TableWidget);

    ui->Items_TableWidget->insertRow(row);

    ui->Items_TableWidget->setItem(row, 0, new QTableWidgetItem());        // ITEM
    ui->Items_TableWidget->setItem(row, 1, new QTableWidgetItem("1"));     // QUANTITY
    ui->Items_TableWidget->setItem(row, 2, new QTableWidgetItem());        // DESCRIPTION
    ui->Items_TableWidget->setItem(row, 3, new QTableWidgetItem("0.00"));  // AMOUNT

    QTableWidgetItem *totalItem = new QTableWidgetItem("0.00");            // TOTAL (computed)
    totalItem->setFlags(totalItem->flags() & ~Qt::ItemIsEditable);
    ui->Items_TableWidget->setItem(row, 4, totalItem);

    ui->Items_TableWidget->setItem(row, 5, new QTableWidgetItem("0.00"));  // TAX

    QPushButton *removeButton = new QPushButton("Remove", this);
    connect(removeButton, &QPushButton::clicked, this, [this, removeButton]() {
        for (int r = 0; r < ui->Items_TableWidget->rowCount(); ++r) {
            if (ui->Items_TableWidget->cellWidget(r, 6) == removeButton) {
                ui->Items_TableWidget->removeRow(r);
                break;
            }
        }
        recalculateInvoiceTotals();
    });
    ui->Items_TableWidget->setCellWidget(row, 6, removeButton);
}

void AddInvoiceDialog::recalculateRowTotal(int row)
{
    QTableWidgetItem *quantityItem = ui->Items_TableWidget->item(row, 1);
    QTableWidgetItem *amountItem = ui->Items_TableWidget->item(row, 3);
    double quantity = quantityItem ? quantityItem->text().toDouble() : 0.0;
    double amount = amountItem ? amountItem->text().toDouble() : 0.0;

    QTableWidgetItem *totalItem = ui->Items_TableWidget->item(row, 4);
    if (!totalItem) {
        totalItem = new QTableWidgetItem();
        totalItem->setFlags(totalItem->flags() & ~Qt::ItemIsEditable);
        ui->Items_TableWidget->setItem(row, 4, totalItem);
    }

    // Writing the TOTAL item would otherwise re-fire cellChanged and loop
    // back into this same recalculation.
    const QSignalBlocker blocker(ui->Items_TableWidget);
    totalItem->setText(QString::number(quantity * amount, 'f', 2));
}

void AddInvoiceDialog::recalculateInvoiceTotals()
{
    double invoiceTotal = 0.0;
    double taxTotal = 0.0;

    for (int row = 0; row < ui->Items_TableWidget->rowCount(); ++row) {
        QTableWidgetItem *totalItem = ui->Items_TableWidget->item(row, 4);
        QTableWidgetItem *taxItem = ui->Items_TableWidget->item(row, 5);
        double total = totalItem ? totalItem->text().toDouble() : 0.0;
        double tax = taxItem ? taxItem->text().toDouble() : 0.0;

        invoiceTotal += total;
        taxTotal += tax * total;
    }

    ui->taxTotal_lineEdit->setText(QString::number(taxTotal, 'f', 2));
    ui->GrandTotal_lineEdit->setText(QString::number(invoiceTotal + taxTotal, 'f', 2));
}

void AddInvoiceDialog::onItemsTableCellChanged(int row, int column)
{
    // QUANTITY (1) or AMOUNT (3) changed: that row's TOTAL is stale.
    if (column == 1 || column == 3) {
        recalculateRowTotal(row);
    }

    // Every path here (including a bare TAX edit) affects the invoice-wide
    // totals.
    recalculateInvoiceTotals();
}

int AddInvoiceDialog::saveCurrentInvoice()
{
    QString clientText = ui->Client_LineEdit->text().trimmed();
    int clientId = resolveSelectedClientId();

    // Build Invoice structure from UI inputs.
    // Note: this layout doesn't collect an invoice-level status, tax rate,
    // or discount, so new invoices always start as "Draft" with tax_rate
    // and discount_amount at 0. The Items table's AMOUNT/TAX columns are
    // not persisted yet either -- there's no invoice_items DAO wired up.
    Invoice newInvoice;
    newInvoice.clientId = clientId;
    newInvoice.invoiceNumber = ui->InvoiceNumber_LineEdit->text().trimmed();
    newInvoice.issueDate = ui->IssueDate_DateEdit->date().toString("yyyy-MM-dd");
    newInvoice.dueDate = ui->DueDate_DateEdit->date().toString("yyyy-MM-dd");
    newInvoice.status = "Draft";
    newInvoice.taxRate = 0;
    newInvoice.discountAmount = 0;
    newInvoice.poNumber = ui->PONumber_LineEdit->text().trimmed();
    newInvoice.notes = ui->Notes_PlainTextEdit->toPlainText().trimmed();

    // Validation
    if (clientText.isEmpty() || clientId == 0) {
        QMessageBox::warning(this, "Validation Error", "Please select a client from the dropdown.");
        return 0;
    }
    if (newInvoice.invoiceNumber.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Invoice Number is required.");
        return 0;
    }
    if (newInvoice.dueDate < newInvoice.issueDate) {
        QMessageBox::warning(this, "Validation Error", "Due date cannot be before the issue date.");
        return 0;
    }

    InvoiceDao invoiceDao(m_dbManager);
    int newId = invoiceDao.insertInvoice(newInvoice);
    if (newId == 0) {
        QMessageBox::critical(this, "Error", "Failed to save invoice to database. The invoice number may already be in use.");
        return 0;
    }

    return newId;
}

void AddInvoiceDialog::resetFormForNewInvoice()
{
    ui->InvoiceNumber_LineEdit->clear();
    ui->IssueDate_DateEdit->setDate(QDate::currentDate());
    ui->NetTerms_ComboBox->setCurrentIndex(kDefaultNetTermsIndex); // also resets Due Date
    ui->PONumber_LineEdit->clear();
    ui->Items_TableWidget->setRowCount(0);
    ui->taxTotal_lineEdit->clear();
    ui->GrandTotal_lineEdit->clear();
    ui->Notes_PlainTextEdit->clear();

    // Client field and its summary are intentionally left as-is, so
    // creating several invoices for the same client in one sitting doesn't
    // require re-picking them each time.
}

void AddInvoiceDialog::on_Cancel_PushButton_clicked()
{
    reject();
}

void AddInvoiceDialog::on_SaveClose_PushButton_clicked()
{
    int newId = saveCurrentInvoice();
    if (newId != 0) {
        emit invoiceSaved(newId);
        accept(); // Close dialog with QDialog::Accepted
    }
}

void AddInvoiceDialog::on_SaveNew_PushButton_clicked()
{
    int newId = saveCurrentInvoice();
    if (newId != 0) {
        emit invoiceSaved(newId);
        resetFormForNewInvoice();
    }
}
