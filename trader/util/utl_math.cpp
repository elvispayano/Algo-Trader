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
  Function:     sig / sig_d
  Inputs:       x (double)
  Output:       y (double)

  Transfer Function Equation:
    f(x) = 1/(1+e^(-x))
    f'(x)= f(x)*(1-f(x))
*/
double Math::sigmoid( double x ) {
  return 1 / ( 1 + exp( -x ) );
}
double Math::sigmoid_d( double x ) {
  return sigmoid( x ) * ( 1 - sigmoid( x ) );
}

/*
  Function:     htan
  Inputs:       x (double)
  Output:       y (double)

  Transfer Function Equation:
    f(x) = (e^x - e^(-x))/(e^x + e^(-x))
    f'(x)= 1 - f(x)^2
*/
double Math::htan( double x ) {
  return tanh( x );
}
double Math::htan_d( double x ) {
  return 1 - htan( x ) * htan( x );
}

/*
  Function:     binary / binary_d
  Inputs:       x (double)
  Output:       y (double)

  Transfer Function Equation:
    f(x) = 1  | x >= 0
    f(x) = 0  | x <  0
    f'(X) = 1 | x == 0
    f'(x) = 0 | x != 0
*/
double Math::binary( double x ) {
  return ( x >= 0 );
}
double Math::binary_d( double x ) {
  return ( x == 0.0 ) ? 1.0 : 0.0;
}

/*
  Function:     relu
  Inputs:       x (double)
  Output:       y (double)

  Transfer Function Equation:
    f(x) = x  | x >  0
    f(x) = 0  | x <= 0
*/
double Math::relu( double x ) {
  return ( x > 0 ) ? x : 0.0;
}
double Math::relu_d( double x ) {
  return ( x > 0 ) ? 1.0 : 0.0;
}

/*
  Function:     linear
  Inputs:       x (double)
  Output:       y (double)

  Transfer Function Equation:
    f(x) = x
    f'(x)= 1
*/
double Math::linear( double x ) {
  return x;
}
double Math::linear_d( double x ) {
  return 1.0;
}
