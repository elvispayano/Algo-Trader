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

// Neural Network Includes
#include "neural_network.h"

// Layer Forward Declaration
#include "layer_base.h"
#include "fully_connected_layer.h"

/*
  Constructor:    Neural Network
  Inputs:         None (void)

  Description:
    Initialize a neural network and initialize layer workspace
    that will be later configured.
*/
NeuralNetwork::NeuralNetwork(std::string ticker) {
  this->ticker = ticker;
  layers.clear();
}

/*
  Destructor:   ~Neural Network
  Inputs:       None (void)

  Description:
    Neural Network is composed of various layer pointers that are
    created. Upon destruction of the Neural Network class, the 
    created pointers must be deleated to prevent a memory leak.
*/
NeuralNetwork::~NeuralNetwork(void) {
  for (size_t i = 0; i < layers.size(); ++i) {
    delete layers[i];
  }
  layers.clear();
}

/*
  Function:     addLayer
  Inputs:       configuration (LayerConfiguration)

  Description:
    Add a new layer to the neural network. The configuration type
    contains all the required elements to select the type of layer,
    the implemented activation, and the size of the layer.
*/
void NeuralNetwork::addLayer(LayerConfiguration configuration) {
  LayerBase* newLayer;
  switch (configuration.Layer) {
  case LayerTypes::FULLYCONNECTED:
    newLayer = new FullyConnectedLayer();
    break;

  default: 
    // LayerTypes::UNKNOWN
    // Unknown layer types are not added to the stack and the return
    // keyword ensures function breaks out and no configuration is
    // attempted
    return;
  }
  
  // Layer configuration
  newLayer->setTF(configuration.Activation);
  newLayer->setInputCount(configuration.layerWidth);
  newLayer->setNodeCount(configuration.layerHeight);

  // Process new configuration
  newLayer->reconfigure();

  // Apply weights & biases
  newLayer->setWeight(configuration.weight);
  newLayer->setBias(configuration.bias);

  if (!layers.empty())
    if (layers.back()->getNodeCount() != newLayer->getInputCount())
      return;

  layers.push_back(newLayer);
}

/*
  Functions:    Process
  Inputs:       Data (dMatrix)
  Outputs:      Action (dMatrix)

  Description:
    Process input data through each layer and return a processed
    matrix containing the desired action to be performed
*/
dMatrix NeuralNetwork::process(dMatrix data) {
  dMatrix action;
  return action;
}
