/*
  Title:
    Neural Network

  Description:
    This Neural Network class is responsible for generating
    and configuring all neural network layers. This class will
    be the main interface for outside implementations.

  Author:
    Elvis Payano
*/

// Standard Includes
#include <vector>

// Utility Includes
#include "network_types.h"
#include "matrix.h"

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

private:
  // Layer Elements
  std::vector<LayerBase*> layers;
};
