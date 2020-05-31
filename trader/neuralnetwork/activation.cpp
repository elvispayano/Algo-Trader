#include "activation.h"
#include <math.h>

Activation::Activation(void) {
  TF = ActivationTypes::NONE;
}

Activation::Activation(ActivationTypes select) {
  TF = select;
}

dMatrix Activation::perform(dMatrix input) {
  dMatrix output(input.Rows(), input.Cols(), 0.0);

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

dMatrix Activation::sig(dMatrix input) {
  dMatrix output(input.Rows(), input.Cols(), 0.0);
  for (size_t r = 0; r < output.Rows(); ++r) {
    for (size_t c = 0; c < output.Cols(); ++c) {
      output(r, c) = 1 / (1 + exp(-input(r,c)));
    }
  }
  return output;
}

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

dMatrix Activation::none(dMatrix input) {
  return input;
}