#ifndef DASHBOARDDATA_H
#define DASHBOARDDATA_H

#include <QString>
#include <QVector>
#include <QtGlobal>

// Plain data passed from DashboardDao to the Dashboard widget. All money is in
// cents; all dates are ISO "yyyy-MM-dd" text, as stored in the database.

struct DashboardSummary {
    qint64 invoicedCents{0};        // billed in the chosen period
    qint64 paymentsCents{0};        // received in the chosen period
    qint64 outstandingCents{0};     // balance due on all open invoices, today
};

struct DashboardInvoiceRow {
    int invoiceId{0};
    QString number;
    QString client;
    QString issueDate;
    QString dueDate;
    qint64 totalCents{0};
    qint64 balanceCents{0};
    int daysPastDue{0};             // 0 for invoices that are not past due
};

// The first N rows to show, plus the count and balance of ALL matching
// invoices (so the panel title can say "Past Due Invoices (212 - $48,100.00)").
struct DashboardInvoiceList {
    QVector<DashboardInvoiceRow> rows;
    int totalCount{0};
    qint64 totalBalanceCents{0};
};

struct DashboardPaymentRow {
    int paymentId{0};
    int invoiceId{0};
    QString date;
    QString client;
    QString invoiceNumber;
    qint64 amountCents{0};
};

struct DashboardMonth {
    QString month;                  // "yyyy-MM"
    qint64 billedCents{0};
    qint64 collectedCents{0};
};

#endif // DASHBOARDDATA_H