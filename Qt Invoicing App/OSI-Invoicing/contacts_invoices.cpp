#include "contacts_invoices.h"
#include "ui_contacts_invoices.h"
#include "DatabaseManager.h"
#include "invoicedao.h"
#include "invoiceitemdao.h"
#include "paymentdao.h"
#include "addinvoicedialog.h"
#include "invoicecard.h"
#include "recordpaymentdialog.h"

#include <QMessageBox>
#include <QPushButton>


Contacts_Invoices::Contacts_Invoices(DatabaseManager& dbManager, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Contacts_Invoices)
    , m_dbManager(dbManager) // Bind reference in initializer list
{
    ui->setupUi(this);

    // Set up table headers (also defined in the .ui file; kept here in case columns change at runtime)
    ui->invoicesTableWidget->setColumnCount(9);
    ui->invoicesTableWidget->setHorizontalHeaderLabels({"Invoice #", "Client", "Issue Date", "Due Date", "Amount", "Payment", "Status", "", ""});

    // Line Edit for Invoice Search Field
    // Place Holder Text
    ui->InvoiceSearch_Field->setPlaceholderText("Search Invoices, Client Name...");
    // Add "Clear" button
    ui->InvoiceSearch_Field->setClearButtonEnabled(true);
    // Add magnifing glass icon to the left side of text box
    QAction *searchAction = new QAction(this);
    searchAction->setIcon(QIcon(":/search.png"));// Path to search icon (Resources file)
    ui->InvoiceSearch_Field->addAction(searchAction, QLineEdit::LeadingPosition);

    // Populate the table with all invoices on first open
    refreshInvoicesTable();
}

Contacts_Invoices::~Contacts_Invoices()
{
    delete ui;
}

void Contacts_Invoices::on_InvoiceSearch_Field_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    refreshInvoicesTable();
}

void Contacts_Invoices::on_StatusFilter_ComboBox_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    refreshInvoicesTable();
}

void Contacts_Invoices::refreshInvoicesTable()
{
    // "All" (index 0) means no status filter -- pass an empty string, which
    // InvoiceDao::searchInvoices treats as "don't filter by status".
    QString statusFilter = ui->StatusFilter_ComboBox->currentIndex() == 0
                                ? QString()
                                : ui->StatusFilter_ComboBox->currentText();

    InvoiceDao invoiceDao(m_dbManager);
    QVector<InvoiceListItem> results = invoiceDao.searchInvoices(ui->InvoiceSearch_Field->text(), statusFilter);
    populateInvoicesTable(results);
}

void Contacts_Invoices::populateInvoicesTable(const QVector<InvoiceListItem> &invoices) {
    ui->invoicesTableWidget->clearContents();
    ui->invoicesTableWidget->setRowCount(invoices.size());

    InvoiceItemDao itemDao(m_dbManager); // reused across rows rather than re-constructed per row
    PaymentDao paymentDao(m_dbManager);

    for (int row = 0; row < invoices.size(); ++row) {
        const InvoiceListItem &invoice = invoices[row];

        QTableWidgetItem *numberItem = new QTableWidgetItem(invoice.invoiceNumber);
        numberItem->setData(Qt::UserRole, invoice.id);

        ui->invoicesTableWidget->setItem(row, 0, numberItem);
        ui->invoicesTableWidget->setItem(row, 1, new QTableWidgetItem(invoice.clientDisplayName));
        ui->invoicesTableWidget->setItem(row, 2, new QTableWidgetItem(invoice.issueDate));
        ui->invoicesTableWidget->setItem(row, 3, new QTableWidgetItem(invoice.dueDate));

        const int totalCents = itemDao.getInvoiceTotalCents(invoice.id);
        auto *amountItem = new QTableWidgetItem(QString("$%1").arg(totalCents / 100.0, 0, 'f', 2));
        amountItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->invoicesTableWidget->setItem(row, 4, amountItem);

        // Computed from actual recorded payments, independent of the
        // manually-set Status field (an invoice can be "Sent" and fully
        // paid, or "Paid" on paper with no payments actually recorded --
        // this column reflects the real payment data, that one doesn't).
        const int paidCents = paymentDao.getTotalPaidForInvoice(invoice.id);
        QString paymentText;
        if (totalCents > 0 && paidCents >= totalCents) {
            paymentText = "Paid";
        } else if (paidCents > 0) {
            paymentText = "Partial";
        } else {
            paymentText = "Unpaid";
        }
        ui->invoicesTableWidget->setItem(row, 5, new QTableWidgetItem(paymentText));

        ui->invoicesTableWidget->setItem(row, 6, new QTableWidgetItem(invoice.status));

        const int invoiceId = invoice.id; // captured by value, not by row index

        QPushButton *editButton = new QPushButton("Edit", this);
        connect(editButton, &QPushButton::clicked, this, [this, invoiceId]() {
            openInvoiceCard(invoiceId);
        });
        ui->invoicesTableWidget->setCellWidget(row, 7, editButton);

        QPushButton *receivePaymentButton = new QPushButton("Receive Payment", this);
        connect(receivePaymentButton, &QPushButton::clicked, this, [this, invoiceId]() {
            openReceivePayment(invoiceId);
        });
        ui->invoicesTableWidget->setCellWidget(row, 8, receivePaymentButton);
    }
}

void Contacts_Invoices::openInvoiceCard(int invoiceId)
{
    InvoiceCard *card = new InvoiceCard(m_dbManager, invoiceId, this);

    // Refresh the results table whenever the card saves a change
    connect(card, &InvoiceCard::invoiceUpdated, this, [this](int) {
        refreshInvoicesTable();
    });

    card->show();
    card->raise();
    card->activateWindow();
}

void Contacts_Invoices::openReceivePayment(int invoiceId)
{
    RecordPaymentDialog dialog(m_dbManager, invoiceId, this);
    if (dialog.exec() == QDialog::Accepted) {
        // Doesn't change invoice.status by itself, but refreshing keeps
        // the row's numbers current with anything else that might have
        // changed, and is cheap enough not to bother checking.
        refreshInvoicesTable();
    }
}

// Add New Invoice
void Contacts_Invoices::on_NewInvoice_Button_clicked()
{
    // No client is known ahead of time from this entry point,
    // so the dialog opens with its client picker unset (0).
    AddInvoiceDialog dialog(m_dbManager, 0, this);

    // Save/New keeps the dialog open for another invoice, so refresh on
    // every save rather than only once the dialog finally closes.
    connect(&dialog, &AddInvoiceDialog::invoiceSaved, this, [this](int) {
        refreshInvoicesTable();
    });

    dialog.exec();
}


// Invoice Search Field
void Contacts_Invoices::on_InvoiceSearch_Field_returnPressed()
{
    // Should be the same as on_InvoiceSearch_Field_textChanged
}
