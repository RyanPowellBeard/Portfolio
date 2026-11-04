#ifndef DAO_DASHBOARD_H
#define DAO_DASHBOARD_H

#include <QSqlDatabase>
#include <QVector>

#include "dashboarddata.h"

class QDate;

// Read-only aggregate queries for the dashboard. Everything is computed in SQL
// so the dashboard stays fast with tens of thousands of imported invoices;
// nothing here loops over invoices calling other DAOs.
//
// The connection is passed in (DatabaseManager::database()); the queries never
// use Qt's default connection. Use it from the thread that owns the connection.
//
// Rules shared by every query:
//  - Draft and Void invoices are never counted (invoices.status).
//  - "Open" / "past due" use the LIVE payment balance (invoice total minus
//    payments), NOT invoices.status, matching the Payment column in
//    Contacts_Invoices.
//  - Open = balance > 0 and due today or later (or no due date).
//    Past due = balance > 0 and due before today. They never overlap.
//
// No schema changes are needed: the indexes these queries use
// (idx_payments_date, idx_payments_invoice, idx_invoice_items_invoice) are
// already created by DatabaseManager::createTables().
class DAO_Dashboard
{
public:
    explicit DAO_Dashboard(const QSqlDatabase& db) : m_db(db) {}

    // Recomputes every counted invoice's total and balance into a temporary
    // table that all the queries below read. Call it once per refresh; it is
    // built automatically the first time a query needs it.
    void rebuildSnapshot() const;

    // 'from'..'to' inclusive.
    DashboardSummary summary(const QDate& from, const QDate& to) const;

    DashboardInvoiceList openInvoices(const QDate& today, int limit) const;
    DashboardInvoiceList pastDueInvoices(const QDate& today, int limit) const;
    QVector<DashboardPaymentRow> recentPayments(int limit) const;

    // 'months' entries ending with the month of 'today', oldest first; months
    // without activity are included with zeros.
    QVector<DashboardMonth> monthlyOverview(const QDate& today, int months) const;

private:
    void ensureSnapshot() const;

    QSqlDatabase m_db;
};

#endif // DAO_DASHBOARD_H