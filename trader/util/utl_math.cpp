//! Utilities Math
//!
//! A collection of math functions that required within the project. All created
//! standard functions should be included here.
//!
//! \author   Elvis Payano
//! \date     01/09/2020
//! \version  0.0.1

// Utility Includes
#include "utl_math.h"

// C++ Standard Includes
#include <cmath>

//! @fn     double sigmoid( double x )
//! @brief  Sigmoid Transfer Function
//!         \f[ f(x) = 1/(1+e^(-x)) \f]
double Math::sigmoid( double x ) {
  return 1 / ( 1 + exp( -x ) );
}

//! @fn     double sigmoid_d( double x )
//! @brief  Derivative of Sigmoid Transfer Function
//!         \f[ f'(x)= f(x)*(1-f(x)) \f]
double Math::sigmoid_d( double x ) {
  return sigmoid( x ) * ( 1 - sigmoid( x ) );
}

//! @fn     double htan( double x )
//! @brief  Hyperbolic Tangent Transfer Function
//!         \f[ f(x) = (e^x - e^(-x))/(e^x + e^(-x)) \f]
double Math::htan( double x ) {
  return tanh( x );
}

//! @fn     double htan_d( double x )
//! @brief  Derivative of Hyperbolic Tangent Transfer Function
//!         \f[ f'(x)= 1 - f(x)^2 \f]
double Math::htan_d( double x ) {
  return 1 - htan( x ) * htan( x );
}

//! @fn     double binary( double x )
//! @brief  Binary Transfer Function
//!         \f[ f(x) = 1  | x >= 0 \f]
//!         \f[ f(x) = 0  | x <  0 \f]
double Math::binary( double x ) {
  return ( x >= 0 );
}

//! @fn     double binary_d( double x )
//! @brief  Derivative of Binary Transfer Function
//!         \f[ f'(X) = 1 | x == 0 \f]
//!         \f[ f'(X) = 1 | x == 0 \f]
double Math::binary_d( double x ) {
  return ( x == 0.0 ) ? 1.0 : 0.0;
}

//! @nf     double relu( double x )
//! @brief  Rectified Linear Unit Transfer Function
//!         \f[ f(x) = x | x >  0 \f]
//!         \f[ f(x) = 0 | x <= 0 \f]
double Math::relu( double x ) {
  return ( x > 0 ) ? x : 0.0;
}

//! @fn     double relu_d( double x )
//! @brief  Derivative of Rectified Linear Unit Transfer Functions
//!         \f[ f'(x) = 1  | x >  0 \f]
//!         \f[ f'(x) = 0  | x <= 0 \f]
double Math::relu_d( double x ) {
  return ( x > 0 ) ? 1.0 : 0.0;
}

//! @fn     double linear( double x )
//! @brief  Linear Transfer Function
//!         \f[ f(x) = x \f]
double Math::linear( double x ) {
  return x;
}

//! @fn     double linear_d( double x )
//! @brief  Derivative of Linear Transfer Function
//!         \f[ f'(x) = 1 \f]
double Math::linear_d( double x ) {
  return 1.0;
}
