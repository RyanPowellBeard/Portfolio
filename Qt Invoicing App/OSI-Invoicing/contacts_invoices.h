#ifndef CONTACTS_INVOICES_H
#define CONTACTS_INVOICES_H

#include <QWidget>
#include <QVector>
#include "invoicedao.h"

// Forward Declaration
class DatabaseManager;

namespace Ui {
class Contacts_Invoices;
}

class Contacts_Invoices : public QWidget
{
    Q_OBJECT

public:
    // Accept DatabaseManager reference in constructor
    explicit Contacts_Invoices(DatabaseManager& dbManager, QWidget *parent = nullptr);
    ~Contacts_Invoices();

private slots:
    void on_NewInvoice_Button_clicked();

    void on_InvoiceSearch_Field_returnPressed();

    void on_InvoiceSearch_Field_textChanged(const QString &arg1);

private:
    // Helper to render search results in the invoices table
    void populateInvoicesTable(const QVector<InvoiceListItem> &invoices);

    void openInvoiceCard(int invoiceId);

    Ui::Contacts_Invoices *ui;
    DatabaseManager& m_dbManager; // Store reference to manager
};

#endif // CONTACTS_INVOICES_H
