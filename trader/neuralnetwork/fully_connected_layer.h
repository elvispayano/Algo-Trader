
#ifndef FULLY_CONNECTED_LAYER_H
#define FULLY_CONNECTED_LAYER_H

// Neural Network Includes
#include "layer_base.h"

// Utilities Includes
#include "matrix.h"

class FullyConnectedLayer : public LayerBase {
public:
  // Constructor
  FullyConnectedLayer(void);
  FullyConnectedLayer(ActivationTypes);

  // Destructor
  ~FullyConnectedLayer(void);

  dMatrix processLayer(dMatrix input);
};

#endif /* FULLY_CONNECTED_LAYER_H */
