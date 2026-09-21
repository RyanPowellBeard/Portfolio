#include "contacts_invoices.h"
#include "ui_contacts_invoices.h"
#include "DatabaseManager.h"
#include "invoicedao.h"
#include "addinvoicedialog.h"
#include "invoicecard.h"

#include <QMessageBox>
#include <QPushButton>

/*
 * This is the page that shows when invoice button is clicked in main window
 */
Contacts_Invoices::Contacts_Invoices(DatabaseManager& dbManager, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Contacts_Invoices)
    , m_dbManager(dbManager) // Bind reference in initializer list
{
    ui->setupUi(this);

    // Set up table headers (also defined in the .ui file; kept here in case columns change at runtime)
    ui->invoicesTableWidget->setColumnCount(6);
    ui->invoicesTableWidget->setHorizontalHeaderLabels({"Invoice #", "Client", "Issue Date", "Due Date", "Status", ""});

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
    on_InvoiceSearch_Field_textChanged(QString());
}

Contacts_Invoices::~Contacts_Invoices()
{
    delete ui;
}

void Contacts_Invoices::on_InvoiceSearch_Field_textChanged(const QString &arg1)
{
    // Create DAO instance passing m_dbManager reference
    InvoiceDao invoiceDao(m_dbManager);

    // Fetch matched results from DAO (returns QVector<InvoiceListItem>)
    QVector<InvoiceListItem> results = invoiceDao.searchInvoices(arg1);

    // Render results in table
    populateInvoicesTable(results);
}

void Contacts_Invoices::populateInvoicesTable(const QVector<InvoiceListItem> &invoices) {
    ui->invoicesTableWidget->clearContents();
    ui->invoicesTableWidget->setRowCount(invoices.size());

    for (int row = 0; row < invoices.size(); ++row) {
        const InvoiceListItem &invoice = invoices[row];

        QTableWidgetItem *numberItem = new QTableWidgetItem(invoice.invoiceNumber);
        numberItem->setData(Qt::UserRole, invoice.id);

        ui->invoicesTableWidget->setItem(row, 0, numberItem);
        ui->invoicesTableWidget->setItem(row, 1, new QTableWidgetItem(invoice.clientDisplayName));
        ui->invoicesTableWidget->setItem(row, 2, new QTableWidgetItem(invoice.issueDate));
        ui->invoicesTableWidget->setItem(row, 3, new QTableWidgetItem(invoice.dueDate));
        ui->invoicesTableWidget->setItem(row, 4, new QTableWidgetItem(invoice.status));

        QPushButton *editButton = new QPushButton("Edit", this);
        const int invoiceId = invoice.id; // captured by value, not by row index
        connect(editButton, &QPushButton::clicked, this, [this, invoiceId]() {
            openInvoiceCard(invoiceId);
        });
        ui->invoicesTableWidget->setCellWidget(row, 5, editButton);
    }
}

void Contacts_Invoices::openInvoiceCard(int invoiceId)
{
    InvoiceCard *card = new InvoiceCard(m_dbManager, invoiceId, this);

    // Refresh the results table whenever the card saves a change
    connect(card, &InvoiceCard::invoiceUpdated, this, [this](int) {
        on_InvoiceSearch_Field_textChanged(ui->InvoiceSearch_Field->text());
    });

    card->show();
    card->raise();
    card->activateWindow();
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
        on_InvoiceSearch_Field_textChanged(ui->InvoiceSearch_Field->text());
    });

    dialog.exec();
}


// Invoice Search Field
void Contacts_Invoices::on_InvoiceSearch_Field_returnPressed()
{
    // Should be the same as on_InvoiceSearch_Field_textChanged
}
