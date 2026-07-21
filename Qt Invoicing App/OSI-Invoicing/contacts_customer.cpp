#include "contacts_customer.h"
#include "ui_contacts_customer.h"

Contacts_Customer::Contacts_Customer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Contacts_Customer)
{
    ui->setupUi(this);

    // Line Edit for Customer Search Field
    // Place Holder Text
    ui->CustomerSearch_Field->setPlaceholderText("Search Customers, Contact Information...");
    // Add "Clear" button
    ui->CustomerSearch_Field->setClearButtonEnabled(true);
    // Add magnifing glass icon to the left side of text box
    QAction *searchAction = new QAction(this);
    searchAction->setIcon(QIcon(":/search.png"));// Path to search icon (Resources file)
    ui->CustomerSearch_Field->addAction(searchAction, QLineEdit::LeadingPosition);


}

// Search Box Options---------------------------------------------------------------------------
/* Real-Time Search Choice A....
 * connect(ui->CustomerSearch_Field, &QLineEdit::textChanged, this, &MainWindow::performSearch);
 *
 * Search on "Enter" Choice B (Better for large db)
 * connect(ui->CustomerSearch_Field, &QLineEdit::returnPressed, this, &MainWindow::performSearch);
 *
 * If the invoices are being displayed in QTableView or QTreeView, the best way to wire up the new
 * search box is using QSortFilterProxyModel. You would feed your db layout into the proxy model,
 * and then you can connect your QLineEdit directly to is like the following...
 *
 * // Single line will instantly filter the entire table as the user types
 * connect(ui->CustomerSearch_Field, &QLineEdit::textChanged, ui->proxymodle, &QSortFilterModel::setFilterFixedString);
 */

Contacts_Customer::~Contacts_Customer()
{
    delete ui;
}

// Add New Customer
void Contacts_Customer::on_NewCustomer_Button_clicked()
{

}


// CSV Import
void Contacts_Customer::on_CsvImport_Button_clicked()
{

}


// Customer Search Field
void Contacts_Customer::on_CustomerSearch_Field_returnPressed()
{

}


