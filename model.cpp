#include "model.h"
namespace ModelNS
{

Model::Model() : t(n), x(n, 3)
{
    init();
}

void Model::solve()
{
    bool firstTime = true;

    while ( s1 < s1k )
    {
        if ( !firstTime )
            s1 += dS;

        // 1.13
        double
                gam_th = l * cos(s1),
                w_th = l * sin(s1),
                del_th = s2;

        // 1.18, 1.19
         double
                 A = c1*l*sin(s1) - l*cos(s1) - c2*s2,
                 lambda = 1 / (   sin( s1*(A-ksi_max) )   );

         if ( s1 > 0 && s1 < 3.14 )
         {
             psi_gam_0 = cotan(s1) / (A-ksi_max); //-inf, тк ctg(0)
             psi_w_0 = 1 / (A-ksi_max);
         }
         else if ( s1 > 3.14 && s1 < 2*3.14 ) // TO DO: нужна ли проверка
         {
             psi_gam_0 = cotan(s1) / (A+ksi_max); //inf
             psi_w_0 = 1 / (A+ksi_max);
         }

         double u, ksi;
         // решение системы 1.21
         for (int i = 1; i < n; ++i)
         {
             // 1.8
             double tmp1 = psi_del(t[i-1]); //-nan
               u =  -u_max * sign( psi_del(t[i-1]) );

             double tmp2 = psi_w(t[i-1]); //inf
             ksi = ksi_max * sign(   psi_w(t[i-1]) );

             x.setRow( i,  rungeKuttaStep(x.getRow(i-1), u, ksi) );
         }

         firstTime = false;
    }
}

void Model::init()
{
    for (int i = 0; i < n; ++i)
            t[i] = i * dt;

    x.setRow( 0,  {2.5 * 3.14/180,  5 * 3.14/180,  0} );  // inits
//    x.setRow( 0,  {-2.5 * 3.14/180,  30 * 3.14/180,  0} );  // inits
}

MathNS::Vector<double> Model::calcDerivative(const MathNS::Vector<double> &x, double u, double ksi) const
{
    double
        gam = x[0],
          w = x[1],
        del = x[2];

    MathNS::Vector<double> dx_dt(3);

    dx_dt[0] = -w;                   ///< gamma
    dx_dt[1] = c1*w - c2*del - ksi;  ///< w
    dx_dt[2] = -k/T * u + del/T;     ///< delta

    return dx_dt;
}

MathNS::Vector<double> Model::rungeKuttaStep( const MathNS::Vector<double> & x_curr, double u, double ksi) const
{
    const MathNS::Vector<double>
    k1 = calcDerivative(              x_curr,    u, ksi),
    k2 = calcDerivative(x_curr  +  k1/2 * dt,    u, ksi),
    k3 = calcDerivative(x_curr  +  k2/2 * dt,    u, ksi),
    k4 = calcDerivative(x_curr  +    k3 * dt,    u, ksi);

    return x_curr + (k1 + k2*2 + k3*2 + k4) / 6 * dt;
}

}
