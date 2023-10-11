#pragma once
#include <QWidget>
#include <qwt_plot_canvas.h>
#include <qwt_legend.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_plot.h>

namespace PlotWidgetNS
{

/*!
    @brief Класс для отрисовки графика на двумерных осях
*/
class PlotWidget : public QWidget
{
    Q_OBJECT

public:
    PlotWidget(const QString & xLabel, const QString & yLabel,
           QWidget *parent = nullptr);

    void addGraph(const QString &name, const Qt::GlobalColor color,
                  const std::vector<double> & xData, const std::vector<double> & yData );

private:

    QwtPlot * plot;

    QString xLabel, yLabel;

    void setup();

    void setupPlot();

    void setupWheelZooming();

    void createLegend();
};

}
