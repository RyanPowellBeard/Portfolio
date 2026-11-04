#ifndef DASH_BOARD_H
#define DASH_BOARD_H

#include <QDate>
#include <QWidget>

#include "DAO_Dashboard.h"

class BarChartWidget;
class QComboBox;
class QGroupBox;
class QLabel;
class QTableWidget;
class DatabaseManager;

class Dash_Board : public QWidget
{
    Q_OBJECT

public:
    explicit Dash_Board(DatabaseManager& dbManager, QWidget* parent = nullptr);

public slots:
    void refresh();

signals:
    void invoiceOpenRequested(int invoiceId);

protected:
    void showEvent(QShowEvent* event) override;

private:
    enum Period { Last7Days, Last30Days, Last90Days, ThisMonth, ThisYear };

    QDate periodStart(const QDate& today) const;
    void fillInvoiceTable(QTableWidget* table, const DashboardInvoiceList& list, bool pastDue);
    void fillPaymentTable(const QVector<DashboardPaymentRow>& rows);
    void fillChart(const QDate& today);

    DatabaseManager& m_dbManager;
    DAO_Dashboard m_dao;

    BarChartWidget* m_chart{nullptr};
    QComboBox* m_periodCombo{nullptr};
    QLabel* m_invoicedValue{nullptr};
    QLabel* m_paymentsValue{nullptr};
    QLabel* m_outstandingValue{nullptr};
    QGroupBox* m_openBox{nullptr};
    QGroupBox* m_pastDueBox{nullptr};
    QTableWidget* m_openTable{nullptr};
    QTableWidget* m_pastDueTable{nullptr};
    QTableWidget* m_paymentTable{nullptr};
};

#endif // DASH_BOARD_H