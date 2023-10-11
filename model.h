#pragma once
#include "mathematics.h"
namespace ModelNS
{

class Model
{
public:
    Model();

    void solve();

    MathNS::Vector<double> gamma() const  { return x.getCol(0); }
    MathNS::Vector<double> omega() const  { return x.getCol(1); }

private:

    void init();

    MathNS::Vector<double> calcDerivative(const MathNS::Vector<double> & x, double u, double ksi) const;

    MathNS::Vector<double> rungeKuttaStep( const MathNS::Vector<double> & x_curr, double u, double ksi) const;

    double psi_w( double t )  { return psi_gam_0*(1-exp(-c1*t))/c1 + psi_w_0*exp(-c1*t); }

    double psi_del( double t )  { return exp(-t/T) * ( psi_del_0 + (c2*T*psi_gam_0/c1)*(exp(t/T)-1) +
                                         c2*(psi_w_0 - psi_gam_0/c1)*T / (1-c1*T) * (exp((1-c1*T)*t/T)-1) ); }

        const double
                dt = 0.01,   ///< Интервал поступления новых измерений (шаг процесса)
                t_end = 0.5; ///< Время окончания моделирования

        const int n = ceil( t_end / dt + 1 ); ///< Количество итераций в процессе моделирования

        double
            c1 = 2,
            c2 = 4,
            T = 1.5,
            k = 1,
            u_max = 1,
            ksi_max = 4,
            s1 = 0*3.14/180,
            s2 = 0,
            s1k = 2 * 3.14,
            dS = 2.5,
            l = 0.25,
            psi_gam_0,
            psi_w_0,
            psi_del_0 = 0;

        MathNS::Vector<double> t;
        MathNS::Matrix<double> x; ///< вектор состояния во времени размерности [nx3]
};

}

