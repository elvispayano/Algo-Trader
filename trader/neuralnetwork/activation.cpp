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
Activation::Activation(void) {
  setTF(ActivationTypes::LINEAR);
}

/*
  Constructor:  Activation
  Inputs:       tfSelect (ActivationTypes [enum])

  Description:
    Configure the activation transfer function with provided
    parameters
*/
Activation::Activation(ActivationTypes tfSelect) {
  setTF(tfSelect);
}

/*
  Destructor:   ~Activation
  Inputs:       None (void)

  Description:
    Clear any dynamically allocated memory
*/
Activation::~Activation(void) {

}

/*
  Function:     setTF
  Inputs:       selector

  Description:
    Configure activation transfer function to be used
    by layers
*/
void Activation::setTF(ActivationTypes selector) {
  tfType = selector;
  switch (tfType) {
  case ActivationTypes::SIGMOID:
    transferFunction = sigmoid;
    break;

  case ActivationTypes::TANH:
    transferFunction = htan;
    break;

  case ActivationTypes::BINARY:
    transferFunction = binary;
    break;

  case ActivationTypes::RELU:
    transferFunction = relu;
    break;

  default: // ActivationTypes::LINEAR
    transferFunction = linear;
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
dMatrix Activation::performTF(dMatrix input) {
  input.forEach(transferFunction);
  return input;
}
