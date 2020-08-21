/*
  Title:
    Utl Math

  Description:
    This library contains standard math functions that are
    required within the project. All created standard functions
    should be included here.

  Tests:
    test_utl_math.cc

  Author:
    Elvis Payano
*/

// Utility Includes
#include "utl_math.h"

// C++ Standard Includes
#include <cmath>

/*
  Function:     sig
  Inputs:       x (double)
  Output:       y (double)

  Description:
    Process input through Sigmoid transfer function.

  Transfer Function Equation:
    f(x) = 1/(1+e^(-x))
*/
double sigmoid( double x ) {
  return 1 / ( 1 + exp( -x ) );
}

/*
  Function:     htan
  Inputs:       x (double)
  Output:       y (double)

  Description:
    Process input through Hyperbolic Tangent transfer
    function.

  Transfer Function Equation:
    f(x) = (e^x - e^(-x))/(e^x + e^(-x))
*/
double htan( double x ) {
  return ( exp( x ) - exp( -x ) ) / ( exp( x ) + exp( -x ) );
}

/*
  Function:     binary
  Inputs:       x (double)
  Output:       y (double)

  Description:
    Process input through Binary transfer function.

  Transfer Function Equation:
    f(x) = 1  | x >= 0
    f(x) = 0  | x <  0
*/
double binary( double x ) {
  return ( x >= 0 );
}

/*
  Function:     relu
  Inputs:       x (double)
  Output:       y (double)

  Description:
    Process input through Recitified Linear Unit
    transfer function.

  Transfer Function Equation:
    f(x) = x  | x >  0
    f(x) = 0  | x <= 0
*/
double relu( double x ) {
  return ( x > 0 ) ? x : 0;
}

/*
  Function:     lin
  Inputs:       x (double)
  Output:       y (double)

  Description:
    No processing of inputs through a transfer
    function.

  Transfer Function Equation:
    f(x) = x
*/
double linear( double x ) {
  return x;
}
