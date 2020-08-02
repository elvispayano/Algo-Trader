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
#include <string>

// Utility Includes
#include "matrix.h"
#include "network_types.h"

// Forward Declaration
class LayerBase;

class NeuralNetwork {
public:
  // Constructor
  NeuralNetwork(std::string ticker);

  // Destructor
  ~NeuralNetwork(void);

  // Layer Configuration
  void addLayer(LayerConfiguration configuration);
  size_t getLayerCount(void) { return layers.size(); }
  unsigned int getTotalNodes(void);

  // Network Identification
  virtual std::string getTicker(void) { return ticker; }

  // Process Network Inputs
  virtual dMatrix process(dMatrix data);

  // Train neural network
  void train(void) {}
  void setTrainParams(NetworkTrainingParams params) {}

private:
  // Layer Elements
  std::vector<LayerBase*> layers;
  std::string ticker;
};

#endif /* NEURAL_NETWORK_H */
