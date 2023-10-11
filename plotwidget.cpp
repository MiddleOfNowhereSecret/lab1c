#include "plotwidget.h"
#include <QVBoxLayout>
#include <QVector>

namespace PlotWidgetNS
{

PlotWidget::PlotWidget(const QString &xLabel, const QString &yLabel, QWidget *parent)
    : QWidget(parent),
      xLabel( xLabel ),
      yLabel( yLabel )

{
    setup();
}

void PlotWidget::setup()
{
    resize(400, 400);

    plot = new QwtPlot;
    setupPlot();

    QVBoxLayout * mainLO = new QVBoxLayout;
    mainLO->addWidget( plot );
    setLayout( mainLO );
}

void PlotWidget::setupPlot()
{
    setupWheelZooming();

    plot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    plot->setCanvasBackground(QBrush(Qt::white));

    QwtText Ox(xLabel);
    Ox.setFont( QFont("Courier", 9, QFont::Weight::Bold, true) );
    plot->setAxisTitle(QwtPlot::xBottom, Ox);

    QwtText Oy(yLabel);
    Oy.setFont( QFont("Courier", 9, QFont::Weight::Bold, true)  );
    plot->setAxisTitle(QwtPlot::yLeft, Oy);

    QwtPlotGrid * grid = new QwtPlotGrid;
    grid->attach(plot);
    grid->setPen(QColor(128,128,128, 100));

    createLegend();
}


void PlotWidget::setupWheelZooming()
{
    QwtPlotMagnifier * zoom = new QwtPlotMagnifier(plot->canvas());
    zoom->setAxisEnabled(QwtPlot::xBottom, true);
    zoom->setAxisEnabled(QwtPlot::yLeft, true);

    QwtPlotPanner * plotPanner = new QwtPlotPanner(plot->canvas());
    plotPanner->setMouseButton(Qt::LeftButton);
}


void PlotWidget::createLegend()
{
    QwtLegend * legend = new QwtLegend;

    plot->insertLegend( legend, QwtPlot::LegendPosition::TopLegend );

    plot->legend()->setFont(QFont("Courier", 9));

    plot->replot();
}

void PlotWidget::addGraph(const QString &name, const Qt::GlobalColor color,
                      const std::vector<double> & xData, const std::vector<double> & yData )
{
    QwtPlotCurve * myLine = new QwtPlotCurve( name );
    myLine->setPen( color );
    myLine->setLegendAttribute( QwtPlotCurve::LegendShowLine );

    myLine->setSamples(  QVector<double>::fromStdVector( xData ),
                         QVector<double>::fromStdVector( yData )  );
    myLine->attach(plot);
}

}
