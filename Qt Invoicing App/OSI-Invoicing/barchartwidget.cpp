#include "barchartwidget.h"

#include <QLocale>
#include <QMouseEvent>
#include <QPainter>
#include <QToolTip>
#include <cmath>

namespace {

// Rounds a raw step up to 1, 2, 5 or 10 times a power of ten.
double niceStep(double raw)
{
    if (raw <= 0.0)
        return 1.0;
    const double base = std::pow(10.0, std::floor(std::log10(raw)));
    const double f = raw / base;
    const double nice = f <= 1.0 ? 1.0 : f <= 2.0 ? 2.0 : f <= 5.0 ? 5.0 : 10.0;
    return nice * base;
}

QString compactMoney(double v)
{
    const QString symbol = QLocale().currencySymbol();
    if (v >= 1e6)
        return symbol + QString::number(v / 1e6, 'g', 3) + QLatin1Char('M');
    if (v >= 1e3)
        return symbol + QString::number(v / 1e3, 'g', 3) + QLatin1Char('k');
    return symbol + QString::number(v, 'f', 0);
}

} // namespace

BarChartWidget::BarChartWidget(QWidget* parent)
    : QWidget(parent)
{
    setMouseTracking(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void BarChartWidget::setData(const QStringList& categories,
                             const QVector<Series>& series,
                             const QStringList& tooltipTitles)
{
    m_categories = categories;
    m_series = series;
    m_titles = tooltipTitles.size() == categories.size() ? tooltipTitles : categories;
    m_hover = -1;
    update();
}

int BarChartWidget::categoryAt(const QPointF& pos) const
{
    const int n = m_categories.size();
    if (n == 0 || !m_plot.contains(pos))
        return -1;
    const int index = int((pos.x() - m_plot.left()) / (m_plot.width() / n));
    return qBound(0, index, n - 1);
}

void BarChartWidget::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    const QColor text = palette().color(QPalette::WindowText);
    QColor grid = text;
    grid.setAlpha(45);

    const int n = m_categories.size();
    double maxValue = 0.0;
    for (const Series& s : m_series)
        for (const double v : s.values)
            maxValue = qMax(maxValue, v);

    if (n == 0 || m_series.isEmpty() || maxValue <= 0.0) {
        m_plot = QRectF();
        p.setPen(text);
        p.drawText(rect(), Qt::AlignCenter, tr("No activity yet"));
        return;
    }

    const QFontMetrics fm(font());
    const double step = niceStep(maxValue / 4.0);
    const double top = step * qMax(1, int(std::ceil(maxValue / step - 1e-9)));

    const int left = fm.horizontalAdvance(compactMoney(top)) + 14;
    const int right = 10;
    const int topMargin = fm.height() + 12;
    const int bottom = fm.height() + 8;
    m_plot = QRectF(left, topMargin, width() - left - right, height() - topMargin - bottom);
    if (m_plot.width() < 40 || m_plot.height() < 30)
        return;

    // Legend, top left.
    qreal legendX = m_plot.left();
    for (const Series& s : m_series) {
        p.setPen(Qt::NoPen);
        p.setBrush(s.color);
        p.drawRect(QRectF(legendX, 4, fm.height() - 4, fm.height() - 4));
        p.setPen(text);
        const int w = fm.horizontalAdvance(s.name);
        p.drawText(QPointF(legendX + fm.height(), 4 + fm.ascent() - 2), s.name);
        legendX += fm.height() + w + 18;
    }

    // Gridlines and y-axis labels.
    for (double v = 0.0; v <= top + step / 2.0; v += step) {
        const qreal y = m_plot.bottom() - m_plot.height() * v / top;
        p.setPen(grid);
        p.drawLine(QPointF(m_plot.left(), y), QPointF(m_plot.right(), y));
        p.setPen(text);
        p.drawText(QRectF(0, y - fm.height() / 2.0, left - 6, fm.height()),
                   Qt::AlignRight | Qt::AlignVCenter, compactMoney(v));
    }

    // Bars and x-axis labels.
    const double groupWidth = m_plot.width() / n;
    const int seriesCount = m_series.size();
    const double barWidth = qMin(26.0, groupWidth * 0.8 / seriesCount);
    const double clusterWidth = barWidth * seriesCount;

    int widestLabel = 0;
    for (const QString& label : m_categories)
        widestLabel = qMax(widestLabel, fm.horizontalAdvance(label));
    const int skip = qMax(1, int(std::ceil((widestLabel + 8) / groupWidth)));

    for (int i = 0; i < n; ++i) {
        const double groupLeft = m_plot.left() + groupWidth * i;

        if (i == m_hover) {
            QColor highlight = text;
            highlight.setAlpha(25);
            p.setPen(Qt::NoPen);
            p.setBrush(highlight);
            p.drawRect(QRectF(groupLeft, m_plot.top(), groupWidth, m_plot.height()));
        }

        const double x0 = groupLeft + (groupWidth - clusterWidth) / 2.0;
        for (int j = 0; j < seriesCount; ++j) {
            const double h = m_plot.height() * m_series.at(j).values.value(i) / top;
            p.setPen(Qt::NoPen);
            p.setBrush(m_series.at(j).color);
            p.drawRect(QRectF(x0 + barWidth * j, m_plot.bottom() - h, barWidth - 1, h));
        }

        if (i % skip == 0) {
            p.setPen(text);
            p.drawText(QRectF(groupLeft, m_plot.bottom() + 3, groupWidth, fm.height()),
                       Qt::AlignHCenter | Qt::AlignTop, m_categories.at(i));
        }
    }
}

void BarChartWidget::mouseMoveEvent(QMouseEvent* event)
{
    const int index = categoryAt(event->position());
    if (index != m_hover) {
        m_hover = index;
        update();
    }
    if (index < 0) {
        QToolTip::hideText();
        return;
    }

    QString tip = m_titles.value(index);
    for (const Series& s : m_series)
        tip += QStringLiteral("\n%1: %2")
                   .arg(s.name, QLocale().toCurrencyString(s.values.value(index)));
    QToolTip::showText(event->globalPosition().toPoint(), tip, this);
}

void BarChartWidget::leaveEvent(QEvent*)
{
    if (m_hover != -1) {
        m_hover = -1;
        update();
    }
    QToolTip::hideText();
}