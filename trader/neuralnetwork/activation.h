/*
  Title:
    Activation

  Description:
    This Activation class is responsible for processing the
    layers output through a desired transfer function. This
    class contains a subset of the functionality that is
    required for the data flow through any given layer.

  Tests:
    test_activation.cc

  Author:
    Elvis Payano
*/

#ifndef ACTIVATION_H
#define ACTIVATION_H

// Utility Includes
#include "matrix.h"
#include "network_types.h"

class Activation {
public:
  // Constructors
  Activation( void );
  Activation( ActivationTypes select );

  // Destructors
  ~Activation( void );

  // Activation Configuration
  void            setTF( ActivationTypes select );
  ActivationTypes getTF( void ) { return tfType; }

  dMatrix performTF( dMatrix );
  dMatrix performBP( dMatrix );

private:
  // Transfer function selection trigger
  double ( *transferFunction )( double );
  double ( *backpropFunction )( double );

  // Process layer values through configured activation function
  ActivationTypes tfType;
};

#endif /*ACTIVATION_H*/
