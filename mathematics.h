#pragma once
#include "matrix.h"
#include <cmath>

double cotan( const double x );

template<typename T>
int sign( T val )
{
    if ( val  > 0 ) return  1;
    if ( val  < 0 ) return -1;
    if ( val == 0 ) return  0;
}


