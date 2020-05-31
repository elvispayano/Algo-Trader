#include "activation.h"

Activation::Activation(void) {
  TF = ActivationTypes::NONE;
}

Activation::Activation(ActivationTypes select) {
  TF = select;
}