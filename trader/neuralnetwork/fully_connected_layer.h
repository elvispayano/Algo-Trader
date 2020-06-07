/*
  Title:
    Fully Connected Layer

  Description:
    A fully connected layer is a layer type in which the each node is
    interconnected, and effects the output based on the configured 
    weights and biases.

  Tests:
    test_fully_connected_layer.cc

  Author:
    Elvis Payano
*/

#ifndef FULLY_CONNECTED_LAYER_H
#define FULLY_CONNECTED_LAYER_H

// Neural Network Includes
#include "layer_base.h"

// Utilities Includes
#include "matrix.h"

class FullyConnectedLayer : public LayerBase {
public:
  // Constructor
  FullyConnectedLayer(void) {};
  FullyConnectedLayer(ActivationTypes);

  // Destructor
  ~FullyConnectedLayer(void) {};

  // Layer update
  dMatrix processLayer(dMatrix input);
};

#endif /* FULLY_CONNECTED_LAYER_H */
