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

// Neural Network Includes
#include "activation.h"

// Utility Includes
#include "utl_math.h"

/*
  Constructor:  Activation
  Inputs:       None (void)

  Description:
    Configure the activation transfer function to  default
    settings
*/
Activation::Activation( void ) {
  setTF( ActivationTypes::LINEAR );
}

/*
  Constructor:  Activation
  Inputs:       tfSelect (ActivationTypes [enum])

  Description:
    Configure the activation transfer function with provided
    parameters
*/
Activation::Activation( ActivationTypes tfSelect ) {
  setTF( tfSelect );
}

/*
  Destructor:   ~Activation
  Inputs:       None (void)

  Description:
    Clear any dynamically allocated memory
*/
Activation::~Activation( void ) {}

/*
  Function:     setTF
  Inputs:       selector

  Description:
    Configure activation transfer function to be used
    by layers
*/
#include <functional>
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

/*
  Function:     performTF
  Inputs:       input (dMatrix)
  Output:       output (dMatrix)

  Description:
    Process layers inputs through the selected transfer
    function. The input is an m-by-n matrix and the output
    will be of the same size
*/
dMatrix Activation::performTF( dMatrix input ) {
  input.forEach( transferFunction );
  return input;
}

/*
  Function:    performBP
  Inputs:      input (dMatrix)
  Output:      output (dMatrix)

  Description:
    Apply the back propagation function to the input
*/
dMatrix Activation::performBP( dMatrix input ) {
  input.forEach( backpropFunction );
  return input;
}
