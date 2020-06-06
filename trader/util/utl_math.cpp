
// Utility Includes
#include "utl_math.h"

// C++ Standard Includes
#include <cmath>

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
dMatrix sig(dMatrix input) {
  dMatrix output(input.Rows(), input.Cols(), 0.0);
  for (size_t r = 0; r < output.Rows(); ++r) {
    for (size_t c = 0; c < output.Cols(); ++c) {
      output(r, c) = 1 / (1 + exp(-input(r, c)));
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
dMatrix tanh(dMatrix input) {
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
dMatrix bin(dMatrix input) {
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
dMatrix relu(dMatrix input) {
  dMatrix output(input.Rows(), input.Cols(), 0.0);
  for (size_t r = 0; r < output.Rows(); ++r) {
    for (size_t c = 0; c < output.Cols(); ++c) {
      if (input(r, c) > 0) output(r, c) = input(r, c);
      else output(r, c) = 0;
    }
  }
  return output;
}

/*
  Function:     lin
  Inputs:       input (dMatrix)
  Output:       output (dMatrix)

  Description:
    No processing of inputs through a transfer function

  Transfer Function Equation:
    f(x) = f(x)
*/
dMatrix lin(dMatrix input) {
  return input;
};