/*
  Title:
    Activation

  Description:
    This Activation class is responsible for processing the
    layers output through a desired transfer function. This
    class contains a subset of the functionality that is
    required for the data flow through any given layer.

  Author:
    Elvis Payano
*/

// Neural Network Includes
#include "activation.h"

// C++ Standard Includes
#include <cmath>

/*
    Constructor:  Activation
    Inputs:       None (void)
    
    Description:
      Configure the activation transfer function to  default
      settings
*/ 
Activation::Activation(void) {
  TF = ActivationTypes::NONE;
}

/*
    Constructor:  Activation
    Inputs:       tfSelect (ActivationTypes [enum])

    Description:
      Configure the activation transfer function with provided
      parameters
*/
Activation::Activation(ActivationTypes tfSelect) {
  TF = tfSelect;
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
    Function:     performTF
    Inputs:       input (dMatrix)
    Output:       output (dMatrix)

    Description:
      Process layers inputs through the selected transfer
      function. The input is an m-by-n matrix and the output
      will be of the same size
*/
dMatrix Activation::performTF(dMatrix input) {
  // Initialize output
  dMatrix output(input.Rows(), input.Cols(), 0.0);

  // Use activation configuration to select which transfer
  // function to use
  switch (TF) {
  case ActivationTypes::SIGMOID:
    output = sig(input);
    break;

  case ActivationTypes::TANH:
    output = tanh(input);
    break;

  case ActivationTypes::BINARY:
    output = bin(input);
    break;

  case ActivationTypes::RELU:
    output = relu(input);
    break;

  default: //ActivationTypes::NONE
    output = input;
  }

  return output;
}

/*
    Function:     sig
    Inputs:       input (dMatrix)
    Output:       output (dMatrix)

    Description:
      Process all entries in the input matrix through
      the Sigmoid transfer function.

    Transfer Function Equation:
      f(x) = 1/(1+e^(-x))
*/
dMatrix Activation::sig(dMatrix input) {
  dMatrix output(input.Rows(), input.Cols(), 0.0);
  for (size_t r = 0; r < output.Rows(); ++r) {
    for (size_t c = 0; c < output.Cols(); ++c) {
      output(r, c) = 1 / (1 + exp(-input(r,c)));
    }
  }
  return output;
}

/*
    Function:     tanh
    Inputs:       input (dMatrix)
    Output:       output (dMatrix)

    Description:
      Process all entries in the input matrix through
      the Hyperbolic Tangent transfer function.

    Transfer Function Equation:
      f(x) = (e^x - e^(-x))/(e^x + e^(-x))
*/
dMatrix Activation::tanh(dMatrix input) {
  dMatrix output(input.Rows(), input.Cols(), 0.0);
  for (size_t r = 0; r < output.Rows(); ++r) {
    for (size_t c = 0; c < output.Cols(); ++c) {
      double x = input(r, c);
      output(r, c) = (exp(x) - exp(-x)) / (exp(x) + exp(-x));
    }
  }
  return output;
}

/*
    Function:     bin
    Inputs:       input (dMatrix)
    Output:       output (dMatrix)

    Description:
      Process all entries in the input matrix through
      the Binary transfer function.

    Transfer Function Equation:
      f(x) = 1   | x >= 0
      f(x) = 0   | x <  0
*/
dMatrix Activation::bin(dMatrix input) {
  dMatrix output(input.Rows(), input.Cols(), 0.0);
  for (size_t r = 0; r < output.Rows(); ++r) {
    for (size_t c = 0; c < output.Cols(); ++c) {
      if (input(r, c) >= 0) output(r, c) = 1;
      else output(r, c) = 0;
    }
  }
  return output;
}

/*
    Function:     relu
    Inputs:       input (dMatrix)
    Output:       output (dMatrix)

    Description:
      Process all entries in the input matrix through
      the Rectified Linear Unit transfer function.

    Transfer Function Equation:
      f(x) = x   | x >  0
      f(x) = 0   | x <= 0
*/
dMatrix Activation::relu(dMatrix input) {
  dMatrix output(input.Rows(), input.Cols(), 0.0);
  for (size_t r = 0; r < output.Rows(); ++r) {
    for (size_t c = 0; c < output.Cols(); ++c) {
      if (input(r, c) > 0) output(r, c) = input(r,c);
      else output(r, c) = 0;
    }
  }
  return output;
}

/*
    Function:     none
    Inputs:       input (dMatrix)
    Output:       output (dMatrix)

    Description:
      No processing of inputs through a transfer function

    Transfer Function Equation:
      f(x) = f(x)
*/
dMatrix Activation::none(dMatrix input) {
  return input;
}
