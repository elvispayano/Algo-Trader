//! Utilities Math
//!
//! A collection of math functions that required within the project. All created
//! standard functions should be included here.
//!
//! \author   Elvis Payano
//! \date     01/09/2020
//! \version  0.0.1

#ifndef UTL_MATH_H
#define UTL_MATH_H

class Math {
public:
  //! @fn     double binary( double x )
  //! @brief  Binary Transfer Function
  //!         \f[ f(x) = 1  | x >= 0 \f]
  //!         \f[ f(x) = 0  | x <  0 \f]
  static double binary( double x );

  //! @nf     double relu( double x )
  //! @brief  Rectified Linear Unit Transfer Function
  //!         \f[ f(x) = x | x >  0 \f]
  //!         \f[ f(x) = 0 | x <= 0 \f]
  static double relu( double x );

  //! @fn     double htan( double x )
  //! @brief  Hyperbolic Tangent Transfer Function
  //!         \f[ f(x) = (e^x - e^(-x))/(e^x + e^(-x)) \f]
  static double htan( double x );

  //! @fn     double linear( double x )
  //! @brief  Linear Transfer Function
  //!         \f[ f(x) = x \f]
  static double linear( double x );

  //! @fn     double sigmoid( double x )
  //! @brief  Sigmoid Transfer Function
  //!         \f[ f(x) = 1/(1+e^(-x)) \f]
  static double sigmoid( double x );

  //! @fn     double binary_d( double x )
  //! @brief  Derivative of Binary Transfer Function
  //!         \f[ f'(X) = 1 | x == 0 \f]
  //!         \f[ f'(X) = 1 | x == 0 \f]
  static double binary_d( double x );

  //! @fn     double htan_d( double x )
  //! @brief  Derivative of Hyperbolic Tangent Transfer Function
  //!         \f[ f'(x)= 1 - f(x)^2 \f]
  static double htan_d( double x );

  //! @fn     double linear_d( double x )
  //! @brief  Derivative of Linear Transfer Function
  //!         \f[ f'(x) = 1 \f]
  static double linear_d( double x );

  //! @fn     double relu_d( double x )
  //! @brief  Derivative of Rectified Linear Unit Transfer Functions
  //!         \f[ f'(x) = 1  | x >  0 \f]
  //!         \f[ f'(x) = 0  | x <= 0 \f]
  static double relu_d( double x );

  //! @fn     double sigmoid_d( double x )
  //! @brief  Derivative of Sigmoid Transfer Function
  //!         \f[ f'(x)= f(x)*(1-f(x)) \f]
  static double sigmoid_d( double x );
};

#endif /* UTL_MATH_H */
