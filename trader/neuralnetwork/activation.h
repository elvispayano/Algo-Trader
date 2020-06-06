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

#ifndef ACTIVATION_H
#define ACTIVATION_H

// Neural Network Includes
#include "activation_types.h"

// Utility Includes
#include "matrix.h"

class Activation {
public:
  // Constructors
  Activation(void);
  Activation(ActivationTypes select);

  // Destructors
  ~Activation(void);

  // Activation Configuration
  void setTF(ActivationTypes select);

protected:
  // Process layer values through configured activation function
  dMatrix performTF(dMatrix);

private:
  // Transfer funciton selection trigger
  dMatrix(*transferFunction)(dMatrix);
};

#endif /*ACTIVATION_H*/
