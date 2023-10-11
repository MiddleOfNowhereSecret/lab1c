#include <QApplication>
#include <QDebug>
#include <QTextCodec>
#include "model.h"
#include "plotwidget.h"
using namespace ModelNS;
using namespace PlotWidgetNS;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Model model;
    model.solve();

    PlotWidget gamma_omega( "gam, rad", "omega, rad/s" );
//    gamma_omega.addGraph( "omega(gamma)", Qt::cyan    , model.gamma(), model.omega() );
    gamma_omega.addGraph( "omega(gamma)", Qt::cyan    , model.gamma()*180/3.14, model.omega()*180/3.14 );
    gamma_omega.show();


    return a.exec();
}
