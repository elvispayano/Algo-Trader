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

#ifndef UTL_MATH_H
#define UTL_MATH_H

// Transfer functions
double binary( double x );   // Transfer Function: Binary
double htan( double x );     // Transfer Function: Hyperbolic Tangent
double linear( double x );   // Transfer Function: Linear
double relu( double x );     // Transfer Function: Rectified Linear Unit
double sigmoid( double x );  // Transfer Function: Sigmoid

// Transfer function derivatives
double binary_d( double x );   // Transfer Function Derivative: Binary
double htan_d( double x );     // Transfer Function Derivative: HTan
double linear_d( double x );   // Transfer Function Derivative: Linear
double relu_d( double x );     // Transfer Function Derivative: ReLu
double sigmoid_d( double x );  // Transfer Function Derivative: Sigmoid

#endif /* UTL_MATH_H */
