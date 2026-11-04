#ifndef BARCHARTWIDGET_H
#define BARCHARTWIDGET_H

#include <QColor>
#include <QRectF>
#include <QStringList>
#include <QVector>
#include <QWidget>

// A small grouped bar chart drawn with QPainter (no extra Qt module needed).
// Follows the application palette, shows a legend, and a tooltip with exact
// amounts when the mouse is over a category.
class BarChartWidget : public QWidget
{
    Q_OBJECT

public:
    struct Series {
        QString name;
        QColor color;
        QVector<double> values;     // one per category, in currency units
    };

    explicit BarChartWidget(QWidget* parent = nullptr);

    // 'categories' are the short x-axis labels; 'tooltipTitles' (optional, same
    // length) are the longer names shown in the hover tooltip.
    void setData(const QStringList& categories,
                 const QVector<Series>& series,
                 const QStringList& tooltipTitles = QStringList());

    QSize minimumSizeHint() const override { return QSize(320, 140); }
    QSize sizeHint() const override { return QSize(640, 200); }

protected:
    void paintEvent(QPaintEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void leaveEvent(QEvent* event) override;

private:
    int categoryAt(const QPointF& pos) const;

    QStringList m_categories;
    QStringList m_titles;
    QVector<Series> m_series;
    QRectF m_plot;          // plot area of the last paint, used for hit testing
    int m_hover{-1};
};

#endif // BARCHARTWIDGET_H