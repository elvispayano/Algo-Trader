//! Activation
//!
//! The Activation class is responsible for processing the layers output
//! thorugh a desired transfer function. This class contains a subset of the
//! functionality that is required for the data flow through any given layer
//!
//! \author   Elvis Payano
//! \date     30/08/2020
//! \version  0.0.1

#ifndef ACTIVATION_H
#define ACTIVATION_H

// Utility Includes
#include "utilities/matrix.h"
#include "utilities/network_types.h"

class Activation {
public:
  //! @fn     Activation( void )
  //! @brief  An empty constructor assigned the activation class to have a
  //!         default (Linear) selection.
  Activation( void );

  //! @fn     Activation( ActivationTypes select )
  //! @brief  Set the activation type as the type provided.
  Activation( ActivationTypes select );

  //! @fn     ~Activation( void )
  //! @brief  Clear any allocated memory.
  ~Activation( void );

  //! @fn     setTF( ActivationTypes select )
  //! @brief  Change the activation functions used to the forward and backward
  //!         propagation.
  void setTF( ActivationTypes select );

  //! @fn     getTF( void )
  //! @brief  Return the current configured activation type.
  ActivationTypes getTF( void ) { return tfType; }

  //! @fn     performTF( dMatrix )
  //! @param  input   Matrix used to apply transfer function
  //! @brief  Apply the configured transfer function to the provided matrix.
  dMatrix performTF( dMatrix input );

  //! @fn     performBP( dMatrix )
  //! @param  input   Matrix used to apply backpropagation
  //! @brief  Calculate the transfer function derivative of the provided matrix.
  dMatrix performBP( dMatrix input );

private:
  // Transfer function selection trigger
  double ( *transferFunction )( double );
  double ( *backpropFunction )( double );

  // Process layer values through configured activation function
  ActivationTypes tfType;
};

#endif /*ACTIVATION_H*/
