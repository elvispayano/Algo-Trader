/*
  Title:
    Neural Network

  Description:
    This Neural Network class is responsible for generating
    and configuring all neural network layers. This class will
    be the main interface for outside implementations.

  Tests:
    test_neural_network.cc

  Author:
    Elvis Payano
*/

#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

// Standard Includes
#include <vector>

// Utility Includes
#include "matrix.h"
#include "network_types.h"

// Forward Declaration
class LayerBase;

class NeuralNetwork {
public:
  // Constructor
  NeuralNetwork(void);

  // Destructor
  ~NeuralNetwork(void);

  // Layer Configuration
  void addLayer(LayerConfiguration configuration);
  size_t getLayerCount(void) { return layers.size(); }

  // Network Identification
  void setTicker(char* in) { ticker = in; }
  char* getTicker(void) { return ticker; }

  // Process Network Inputs
  dMatrix process(dMatrix data);

private:
  // Layer Elements
  std::vector<LayerBase*> layers;
  char* ticker;
};

#endif /* NEURAL_NETWORK_H */
