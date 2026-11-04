#include "dash_board.h"
#include "DatabaseManager.h"

#include <QAbstractItemView>
#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QLabel>
#include <QLocale>
#include <QTableWidget>
#include <QVBoxLayout>

#include "barchartwidget.h"

namespace {

const int kRowsPerPanel = 25;
const int kOverviewMonths = 12;

QString money(qint64 cents)
{
    return QLocale().toCurrencyString(double(cents) / 100.0);
}

QString shortDate(const QString& iso)
{
    const QDate date = QDate::fromString(iso.left(10), Qt::ISODate);
    return date.isValid() ? QLocale().toString(date, QLocale::ShortFormat) : iso;
}

QTableWidget* makeTable(const QStringList& headers)
{
    auto* table = new QTableWidget(0, headers.size());
    table->setHorizontalHeaderLabels(headers);
    table->verticalHeader()->setVisible(false);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setAlternatingRowColors(true);
    table->setShowGrid(false);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);   // client
    return table;
}

QTableWidgetItem* textItem(const QString& text, bool rightAligned = false)
{
    auto* item = new QTableWidgetItem(text);
    if (rightAligned)
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    return item;
}

QGroupBox* wrap(const QString& title, QWidget* content)
{
    auto* box = new QGroupBox(title);
    auto* layout = new QVBoxLayout(box);
    layout->addWidget(content);
    return box;
}

} // namespace

Dash_Board::Dash_Board(DatabaseManager& dbManager, QWidget* parent)
    : QWidget(parent)
    , m_dbManager(dbManager)
    , m_dao(m_dbManager.database())
{
    setWindowTitle(tr("Dashboard"));

    auto* grid = new QGridLayout(this);
    grid->setSpacing(10);

    // Row 0: overview graph, full width.
    m_chart = new BarChartWidget;
    grid->addWidget(wrap(tr("Overview - last %1 months").arg(kOverviewMonths), m_chart),
                    0, 0, 1, 2);

    // Row 1 left: recent transactions.
    auto* summaryBox = new QGroupBox(tr("Recent Transactions"));
    auto* summaryLayout = new QVBoxLayout(summaryBox);

    m_periodCombo = new QComboBox;
    m_periodCombo->addItem(tr("Last 7 days"), Last7Days);
    m_periodCombo->addItem(tr("Last 30 days"), Last30Days);
    m_periodCombo->addItem(tr("Last 90 days"), Last90Days);
    m_periodCombo->addItem(tr("This month"), ThisMonth);
    m_periodCombo->addItem(tr("This year"), ThisYear);
    m_periodCombo->setCurrentIndex(m_periodCombo->findData(Last30Days));
    summaryLayout->addWidget(m_periodCombo, 0, Qt::AlignLeft);

    auto* totals = new QGridLayout;
    QFont valueFont = font();
    valueFont.setBold(true);
    valueFont.setPointSizeF(valueFont.pointSizeF() * 1.2);

    const auto addTotal = [&](int row, const QString& label, QLabel*& value) {
        totals->addWidget(new QLabel(label), row, 0);
        value = new QLabel(money(0));
        value->setFont(valueFont);
        value->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        totals->addWidget(value, row, 1);
    };
    addTotal(0, tr("Invoices"), m_invoicedValue);
    addTotal(1, tr("Payments"), m_paymentsValue);
    addTotal(2, tr("Outstanding"), m_outstandingValue);
    totals->setColumnStretch(0, 1);
    summaryLayout->addLayout(totals);
    summaryLayout->addStretch();
    grid->addWidget(summaryBox, 1, 0);

    // Row 1 right: open invoices.
    m_openTable = makeTable({tr("Invoice #"), tr("Client"), tr("Due"), tr("Balance")});
    m_openBox = wrap(tr("Open Invoices"), m_openTable);
    grid->addWidget(m_openBox, 1, 1);

    // Row 2 left: past due invoices.
    m_pastDueTable = makeTable({tr("Invoice #"), tr("Client"), tr("Due"), tr("Balance"),
                                tr("Days late")});
    m_pastDueBox = wrap(tr("Past Due Invoices"), m_pastDueTable);
    grid->addWidget(m_pastDueBox, 2, 0);

    // Row 2 right: recent payments.
    m_paymentTable = makeTable({tr("Date"), tr("Client"), tr("Invoice #"), tr("Amount")});
    grid->addWidget(wrap(tr("Recent Payments"), m_paymentTable), 2, 1);

    grid->setRowStretch(0, 3);
    grid->setRowStretch(1, 4);
    grid->setRowStretch(2, 4);
    grid->setColumnStretch(0, 1);
    grid->setColumnStretch(1, 1);

    // Double-click opens the invoice (column 0 carries the invoice id).
    for (QTableWidget* table : {m_openTable, m_pastDueTable, m_paymentTable}) {
        connect(table, &QTableWidget::cellDoubleClicked, this, [this, table](int row, int) {
            const QTableWidgetItem* item = table->item(row, 0);
            const int invoiceId = item ? item->data(Qt::UserRole).toInt() : 0;
            if (invoiceId > 0)
                emit invoiceOpenRequested(invoiceId);
        });
    }

    connect(m_periodCombo, &QComboBox::currentIndexChanged, this, [this]() {
        refresh();
    });
}

void Dash_Board::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    refresh();
}

QDate Dash_Board::periodStart(const QDate& today) const
{
    switch (m_periodCombo->currentData().toInt()) {
    case Last7Days:
        return today.addDays(-6);
    case Last90Days:
        return today.addDays(-89);
    case ThisMonth:
        return QDate(today.year(), today.month(), 1);
    case ThisYear:
        return QDate(today.year(), 1, 1);
    case Last30Days:
    default:
        return today.addDays(-29);
    }
}

void Dash_Board::refresh()
{
    m_dao.rebuildSnapshot();

    const QDate today = QDate::currentDate();

    const DashboardSummary summary = m_dao.summary(periodStart(today), today);
    m_invoicedValue->setText(money(summary.invoicedCents));
    m_paymentsValue->setText(money(summary.paymentsCents));
    m_outstandingValue->setText(money(summary.outstandingCents));

    fillInvoiceTable(m_openTable, m_dao.openInvoices(today, kRowsPerPanel), false);
    fillInvoiceTable(m_pastDueTable, m_dao.pastDueInvoices(today, kRowsPerPanel), true);
    fillPaymentTable(m_dao.recentPayments(kRowsPerPanel));
    fillChart(today);
}

void Dash_Board::fillInvoiceTable(QTableWidget* table, const DashboardInvoiceList& list,
                                  bool pastDue)
{
    QGroupBox* box = pastDue ? m_pastDueBox : m_openBox;
    const QString base = pastDue ? tr("Past Due Invoices") : tr("Open Invoices");
    box->setTitle(list.totalCount > 0
                      ? tr("%1 (%2 - %3)").arg(base).arg(list.totalCount).arg(money(list.totalBalanceCents))
                      : base);

    table->setRowCount(list.rows.size());
    for (int r = 0; r < list.rows.size(); ++r) {
        const DashboardInvoiceRow& row = list.rows.at(r);

        QTableWidgetItem* number = textItem(row.number);
        number->setData(Qt::UserRole, row.invoiceId);
        table->setItem(r, 0, number);
        table->setItem(r, 1, textItem(row.client));
        table->setItem(r, 2, textItem(shortDate(row.dueDate)));
        table->setItem(r, 3, textItem(money(row.balanceCents), true));
        if (pastDue) {
            QTableWidgetItem* late = textItem(QString::number(row.daysPastDue), true);
            late->setForeground(QColor(192, 57, 43));
            table->setItem(r, 4, late);
        }
    }
}

void Dash_Board::fillPaymentTable(const QVector<DashboardPaymentRow>& rows)
{
    m_paymentTable->setRowCount(rows.size());
    for (int r = 0; r < rows.size(); ++r) {
        const DashboardPaymentRow& row = rows.at(r);

        QTableWidgetItem* date = textItem(shortDate(row.date));
        date->setData(Qt::UserRole, row.invoiceId);
        m_paymentTable->setItem(r, 0, date);
        m_paymentTable->setItem(r, 1, textItem(row.client));
        m_paymentTable->setItem(r, 2, textItem(row.invoiceNumber));
        m_paymentTable->setItem(r, 3, textItem(money(row.amountCents), true));
    }
}

void Dash_Board::fillChart(const QDate& today)
{
    const QVector<DashboardMonth> months = m_dao.monthlyOverview(today, kOverviewMonths);

    QStringList labels;
    QStringList titles;
    BarChartWidget::Series billed{tr("Billed"), QColor(76, 120, 168), {}};
    BarChartWidget::Series collected{tr("Collected"), QColor(89, 161, 79), {}};
    for (const DashboardMonth& m : months) {
        const QDate first = QDate::fromString(m.month + QStringLiteral("-01"), Qt::ISODate);
        labels << QLocale().toString(first, QStringLiteral("MMM"));
        titles << QLocale().toString(first, QStringLiteral("MMMM yyyy"));
        billed.values << double(m.billedCents) / 100.0;
        collected.values << double(m.collectedCents) / 100.0;
    }
    m_chart->setData(labels, {billed, collected}, titles);
}