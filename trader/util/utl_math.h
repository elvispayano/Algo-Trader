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

class Math {
public:
  // Transfer functions
  static double binary( double x );   // Transfer Function: Binary
  static double relu( double x );     // Transfer Function: Rectified Linear Unit
  static double htan( double x );     // Transfer Function: Hyperbolic Tangent
  static double linear( double x );   // Transfer Function: Linear
  static double sigmoid( double x );  // Transfer Function: Sigmoid

  // Transfer function derivatives
  static double binary_d( double x );   // Transfer Function Derivative: Binary
  static double htan_d( double x );     // Transfer Function Derivative: HTan
  static double linear_d( double x );   // Transfer Function Derivative: Linear
  static double relu_d( double x );     // Transfer Function Derivative: ReLu
  static double sigmoid_d( double x );  // Transfer Function Derivative: Sigmoid
};

#endif /* UTL_MATH_H */
