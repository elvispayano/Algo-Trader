//! Activation
//!
//! The Activation class is responsible for processing the layers output
//! thorugh a desired transfer function. This class contains a subset of the
//! functionality that is required for the data flow through any given layer
//!
//! \author   Elvis Payano
//! \date     30/08/2020
//! \version  0.0.1

// Neural Network Includes
#include "neuralnetwork/activation.h"

// Utility Includes
#include "utilities/utl_math.h"

//! @fn     Activation( void )
//! @brief  An empty constructor assigned the activation class to have a
//!         default (Linear) selection.
Activation::Activation( void ) {
  setTF( ActivationTypes::LINEAR );
}

//! @fn     Activation( ActivationTypes select )
//! @brief  Set the activation type as the type provided.
Activation::Activation( ActivationTypes tfSelect ) {
  setTF( tfSelect );
}

//! @fn     ~Activation( void )
//! @brief  Clear any allocated memory.
Activation::~Activation( void ) {}

//! @fn     setTF( ActivationTypes select )
//! @brief  Change the activation functions used to the forward and backward
//!         propagation.
void Activation::setTF( ActivationTypes selector ) {
  tfType = selector;
  switch ( tfType ) {
  case ActivationTypes::SIGMOID:
    transferFunction = Math::sigmoid;
    backpropFunction = Math::sigmoid_d;
    break;

  case ActivationTypes::TANH:
    transferFunction = Math::htan;
    backpropFunction = Math::htan_d;
    break;

  case ActivationTypes::BINARY:
    transferFunction = Math::binary;
    backpropFunction = Math::binary_d;
    break;

  case ActivationTypes::RELU:
    transferFunction = Math::relu;
    backpropFunction = Math::relu_d;
    break;

  default:  // ActivationTypes::LINEAR
    transferFunction = Math::linear;
    backpropFunction = Math::linear_d;
    break;
  }
}

//! @fn     performTF( dMatrix )
//! @param  input   Matrix used to apply transfer function
//! @brief  Apply the configured transfer function to the provided matrix.
dMatrix Activation::performTF( dMatrix input ) {
  input.forEach( transferFunction );
  return input;
}

//! @fn     performBP( dMatrix )
//! @param  input   Matrix used to apply backpropagation
//! @brief  Calculate the transfer function derivative of the provided matrix.
dMatrix Activation::performBP( dMatrix input ) {
  input.forEach( backpropFunction );
  return input;
}
