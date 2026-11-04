#include "DAO_Dashboard.h"

#include <QDate>
#include <QDebug>
#include <QHash>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

// ---------------------------------------------------------------------------
// Tables used (see DatabaseManager::createTables):
//   invoices(invoice_id, client_id, invoice_number, issue_date, due_date,
//            status, taxable, discount_amount)
//   invoice_items(invoice_id, tax_id, line_total)   line_total is in cents,
//            rounded per line (generated column)
//   tax_table(tax_id, tax_rate)
//   payments(payment_id, invoice_id, payment_date, amount)   amount in cents
//   clients(client_id, first_name, last_name, business_name)
//
// INVOICE TOTAL (kBalancesSelect) - must equal
// InvoiceItemDao::getInvoiceTotalCents(). Rules used here:
//   * each line: line_total + tax, where tax = ROUND(line_total * rate) per
//     line, only when the invoice is Taxable (invoices.taxable = 1) and the
//     line has a tax_id;
//   * invoice total = sum of lines - invoices.discount_amount (never below 0).
//   * tax_table.tax_rate may be whole percent (5) or basis points (500); the
//     schema comment allows both, so the unit is detected from the data: a
//     largest rate of 50 or more means basis points. No real sales-tax rate
//     is 50%+ and none is below 0.5%, so the two cannot be confused.
// If getInvoiceTotalCents() rounds tax per invoice instead of per line, or
// ignores the discount, change the 'totals' part of kBalancesSelect to match.
// ---------------------------------------------------------------------------

namespace {

// One row per counted invoice with its tax-inclusive total and live balance.
// It is stored once per refresh in the temp table dash_bal (see
// rebuildSnapshot), so each panel query is cheap instead of re-adding up every
// invoice's line items.
const QString kBalancesSelect = QStringLiteral(
    "WITH rate AS ("
    "  SELECT CASE WHEN COALESCE(MAX(tax_rate), 0) >= 50 THEN 10000.0 ELSE 100.0 END AS divisor"
    "  FROM tax_table),"
    " totals AS ("
    "  SELECT it.invoice_id AS invoice_id,"
    "         SUM(it.line_total"
    "             + CASE WHEN inv.taxable = 1 AND t.tax_rate IS NOT NULL"
    "                    THEN CAST(ROUND(it.line_total * t.tax_rate"
    "                                    / (SELECT divisor FROM rate)) AS INTEGER)"
    "                    ELSE 0 END) AS subtotal_cents"
    "  FROM invoice_items it"
    "  JOIN invoices inv ON inv.invoice_id = it.invoice_id"
    "  LEFT JOIN tax_table t ON t.tax_id = it.tax_id"
    "  GROUP BY it.invoice_id),"
    " paid AS ("
    "  SELECT invoice_id, SUM(amount) AS paid_cents"
    "  FROM payments GROUP BY invoice_id)"
    " SELECT i.invoice_id AS invoice_id, i.invoice_number AS number,"
    "        i.client_id AS client_id, i.issue_date AS issue_date, i.due_date AS due_date,"
    "        MAX(COALESCE(tt.subtotal_cents, 0) - COALESCE(i.discount_amount, 0), 0)"
    "            AS total_cents,"
    "        MAX(COALESCE(tt.subtotal_cents, 0) - COALESCE(i.discount_amount, 0), 0)"
    "            - COALESCE(p.paid_cents, 0) AS balance_cents"
    " FROM invoices i"
    " LEFT JOIN totals tt ON tt.invoice_id = i.invoice_id"
    " LEFT JOIN paid p ON p.invoice_id = i.invoice_id"
    " WHERE i.status NOT IN ('Draft', 'Void')");

const QString kClientName = QStringLiteral(
    "COALESCE(NULLIF(c.business_name, ''),"
    " TRIM(COALESCE(c.first_name, '') || ' ' || COALESCE(c.last_name, '')))");

bool run(QSqlQuery& q, const char* what)
{
    if (q.exec())
        return true;
    qWarning() << "DAO_Dashboard:" << what << "failed:" << q.lastError().text();
    return false;
}

DashboardInvoiceList queryInvoices(const QSqlDatabase& db, bool pastDue,
                                   const QDate& today, int limit)
{
    DashboardInvoiceList list;

    const QString dueCondition = pastDue
                                     ? QStringLiteral("b.due_date IS NOT NULL AND b.due_date <> '' AND b.due_date < :today")
                                     : QStringLiteral("(b.due_date IS NULL OR b.due_date = '' OR b.due_date >= :today)");

    QSqlQuery q(db);
    q.prepare(QStringLiteral(
                  "SELECT b.invoice_id, b.number, ") + kClientName + QStringLiteral(
                  " AS client, b.issue_date, b.due_date, b.total_cents, b.balance_cents,"
                  "        CASE WHEN b.due_date < :today2"
                  "             THEN CAST(julianday(:today3) - julianday(b.due_date) AS INTEGER)"
                  "             ELSE 0 END AS days_past_due,"
                  "        COUNT(*) OVER () AS total_count,"
                  "        SUM(b.balance_cents) OVER () AS total_balance"
                  " FROM dash_bal b LEFT JOIN clients c ON c.client_id = b.client_id"
                  " WHERE b.balance_cents > 0 AND ") + dueCondition + QStringLiteral(
                  " ORDER BY CASE WHEN b.due_date IS NULL OR b.due_date = '' THEN 1 ELSE 0 END,"
                  "          b.due_date, b.invoice_id"
                  " LIMIT :limit"));
    const QString todayText = today.toString(Qt::ISODate);
    q.bindValue(QStringLiteral(":today"), todayText);
    q.bindValue(QStringLiteral(":today2"), todayText);
    q.bindValue(QStringLiteral(":today3"), todayText);
    q.bindValue(QStringLiteral(":limit"), limit);
    if (!run(q, pastDue ? "pastDueInvoices" : "openInvoices"))
        return list;

    while (q.next()) {
        DashboardInvoiceRow row;
        row.invoiceId = q.value(0).toInt();
        row.number = q.value(1).toString();
        row.client = q.value(2).toString();
        row.issueDate = q.value(3).toString();
        row.dueDate = q.value(4).toString();
        row.totalCents = q.value(5).toLongLong();
        row.balanceCents = q.value(6).toLongLong();
        row.daysPastDue = q.value(7).toInt();
        list.totalCount = q.value(8).toInt();
        list.totalBalanceCents = q.value(9).toLongLong();
        list.rows.push_back(row);
    }
    return list;
}

} // namespace

void DAO_Dashboard::rebuildSnapshot() const
{
    QSqlQuery drop(m_db);
    if (!drop.exec(QStringLiteral("DROP TABLE IF EXISTS temp.dash_bal")))
        qWarning() << "DAO_Dashboard: could not drop snapshot:" << drop.lastError().text();

    QSqlQuery create(m_db);
    if (!create.exec(QStringLiteral("CREATE TEMP TABLE dash_bal AS ") + kBalancesSelect))
        qWarning() << "DAO_Dashboard: could not build snapshot:" << create.lastError().text();
}

void DAO_Dashboard::ensureSnapshot() const
{
    QSqlQuery q(m_db);
    if (q.exec(QStringLiteral("SELECT 1 FROM sqlite_temp_master WHERE name = 'dash_bal'"))
        && q.next())
        return;
    rebuildSnapshot();
}

DashboardSummary DAO_Dashboard::summary(const QDate& from, const QDate& to) const
{
    DashboardSummary result;
    ensureSnapshot();

    QSqlQuery q(m_db);
    q.prepare(QStringLiteral(
        "SELECT"
        " COALESCE((SELECT SUM(total_cents) FROM dash_bal"
        "           WHERE issue_date >= :from1 AND issue_date < :to1), 0),"
        " COALESCE((SELECT SUM(amount) FROM payments"
        "           WHERE payment_date >= :from2 AND payment_date < :to2), 0),"
        " COALESCE((SELECT SUM(balance_cents) FROM dash_bal WHERE balance_cents > 0), 0)"));
    const QString fromText = from.toString(Qt::ISODate);
    const QString toText = to.addDays(1).toString(Qt::ISODate);     // half-open range
    q.bindValue(QStringLiteral(":from1"), fromText);
    q.bindValue(QStringLiteral(":to1"), toText);
    q.bindValue(QStringLiteral(":from2"), fromText);
    q.bindValue(QStringLiteral(":to2"), toText);
    if (run(q, "summary") && q.next()) {
        result.invoicedCents = q.value(0).toLongLong();
        result.paymentsCents = q.value(1).toLongLong();
        result.outstandingCents = q.value(2).toLongLong();
    }
    return result;
}

DashboardInvoiceList DAO_Dashboard::openInvoices(const QDate& today, int limit) const
{
    ensureSnapshot();
    return queryInvoices(m_db, false, today, limit);
}

DashboardInvoiceList DAO_Dashboard::pastDueInvoices(const QDate& today, int limit) const
{
    ensureSnapshot();
    return queryInvoices(m_db, true, today, limit);
}

QVector<DashboardPaymentRow> DAO_Dashboard::recentPayments(int limit) const
{
    QVector<DashboardPaymentRow> rows;

    QSqlQuery q(m_db);
    q.prepare(QStringLiteral(
                  "SELECT p.payment_id, p.invoice_id, p.payment_date, ") + kClientName + QStringLiteral(
                  " AS client, i.invoice_number, p.amount"
                  " FROM payments p"
                  " LEFT JOIN invoices i ON i.invoice_id = p.invoice_id"
                  " LEFT JOIN clients c ON c.client_id = i.client_id"
                  " ORDER BY p.payment_date DESC, p.payment_id DESC"
                  " LIMIT :limit"));
    q.bindValue(QStringLiteral(":limit"), limit);
    if (!run(q, "recentPayments"))
        return rows;

    while (q.next()) {
        DashboardPaymentRow row;
        row.paymentId = q.value(0).toInt();
        row.invoiceId = q.value(1).toInt();
        row.date = q.value(2).toString();
        row.client = q.value(3).toString();
        row.invoiceNumber = q.value(4).toString();
        row.amountCents = q.value(5).toLongLong();
        rows.push_back(row);
    }
    return rows;
}

QVector<DashboardMonth> DAO_Dashboard::monthlyOverview(const QDate& today, int months) const
{
    QVector<DashboardMonth> result;
    if (months <= 0)
        return result;
    ensureSnapshot();

    const QDate first = QDate(today.year(), today.month(), 1).addMonths(-(months - 1));
    const QString fromText = first.toString(Qt::ISODate);

    QHash<QString, qint64> billed;
    QHash<QString, qint64> collected;

    QSqlQuery b(m_db);
    b.prepare(QStringLiteral(
        "SELECT substr(issue_date, 1, 7), SUM(total_cents) FROM dash_bal"
        " WHERE issue_date >= :from GROUP BY 1"));
    b.bindValue(QStringLiteral(":from"), fromText);
    if (run(b, "monthlyOverview/billed"))
        while (b.next())
            billed.insert(b.value(0).toString(), b.value(1).toLongLong());

    QSqlQuery c(m_db);
    c.prepare(QStringLiteral(
        "SELECT substr(payment_date, 1, 7), SUM(amount) FROM payments"
        " WHERE payment_date >= :from GROUP BY 1"));
    c.bindValue(QStringLiteral(":from"), fromText);
    if (run(c, "monthlyOverview/collected"))
        while (c.next())
            collected.insert(c.value(0).toString(), c.value(1).toLongLong());

    for (int i = 0; i < months; ++i) {
        DashboardMonth m;
        m.month = first.addMonths(i).toString(QStringLiteral("yyyy-MM"));
        m.billedCents = billed.value(m.month, 0);
        m.collectedCents = collected.value(m.month, 0);
        result.push_back(m);
    }
    return result;
}