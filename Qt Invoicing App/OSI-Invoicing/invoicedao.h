#ifndef INVOICEDAO_H
#define INVOICEDAO_H

#include <QVector>
#include <QString>
#include "invoice.h"

// Forward declaration
class DatabaseManager;

// Lightweight, read-only row shape for list/search views. Joins in the
// client's display name so callers don't need a separate ClientDao lookup
// per row.
struct InvoiceListItem {
    int id{0};
    QString invoiceNumber;
    QString clientDisplayName;
    QString issueDate;
    QString dueDate;
    QString status;
};

// Invoice Data Access Object
class InvoiceDao
{
public:
    explicit InvoiceDao(DatabaseManager& dbManager);

    // Insert a new invoice. Returns the new invoice_id, or 0 on failure.
    int insertInvoice(const Invoice& invoice);

    // Fetch a single invoice by id (returned Invoice.id == 0 if not found)
    Invoice getInvoiceById(int invoiceId) const;

    // Update an existing invoice's editable fields (does not touch invoice_number)
    bool updateInvoice(const Invoice& invoice);

    // Fetch invoices belonging to a given client, most recently issued first
    QVector<Invoice> getInvoicesForClient(int clientId) const;

    // Search invoices by invoice number or client name/business, most recently issued first
    QVector<InvoiceListItem> searchInvoices(const QString& searchTerm) const;

private:
    DatabaseManager& m_dbManager;
};

#endif // INVOICEDAO_H
