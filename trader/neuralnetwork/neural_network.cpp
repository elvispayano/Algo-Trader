//! Neural Network
//!
//! This class is responsible for generating and configuring all the neural
//! network layers. This class is also the main interface for the outside
//! implementation.
//!
//! \author   Elvis Payano
//! \date     04/09/2020
//! \version  0.0.1

// Neural Network Includes
#include "neural_network.h"

// Layer Forward Declaration
#include "fully_connected_layer.h"
#include "layer_base.h"

//! @fn     NeuralNetwork( string name )
//! @brief  Initializa a neural network and layer workspace that will later be
//!         configured
NeuralNetwork::NeuralNetwork( std::string name ) {
  this->ticker = ticker;
  layerList.clear();

  inputCount  = 0;
  outputCount = 0;
}

//! @fn     ~NeuralNetwork( string ticker )
//! @brief  The neural network is composed of various layer pointers that are
//!         created. Upon destruction of the class, the created pointers must be
//!         deleted.
NeuralNetwork::~NeuralNetwork( void ) {
  for ( size_t i = 0; i < layerList.size(); ++i ) {
    delete layerList[i];
  }
  layerList.clear();
}

//! @fn     void addLayer( LayerConfiguration configuration )
//! @brief  Add a new layer to the network. The configuration type contains all
//!         the required elements to select the type of layer, implemented
//!         activation, and the size of the layer.
void NeuralNetwork::addLayer( LayerConfiguration config ) {
  LayerBase* newLayer;
  switch ( config.layer ) {
  case LayerTypes::FULLYCONNECTED:
    newLayer = new FullyConnectedLayer( config.activation );
    break;

  default:
    // LayerTypes::UNKNOWN
    // Unknown layer types are not added to the stack and the return
    // keyword ensures function breaks out and no configuration is
    // attempted
    return;
  }

  // Layer configuration
  unsigned int inputs =
      ( layerList.size() > 0 ) ? layerList.back()->getNodeCount() : inputCount;

  newLayer->reconfigure( config.nodes, inputs, config.hyperparams );

  layerList.push_back( newLayer );
}

//! @fn     dMatrix process( dMatrix data )
//! @brief  Process input data through each layer and return a proccessed matrix
//!         containing the desired action to be performed.
dMatrix NeuralNetwork::process( dMatrix data ) {
  dMatrix action;
  return action;
}

//! @fn     unsigned int getTotalNodes( void )
//! @brief  Total nodes used within the network. It is used to determine
//!         approximate complexity.
unsigned int NeuralNetwork::getTotalNodes( void ) {
  unsigned int nodeCount = 0;
  for (LayerBase* layer : layerList) {
    nodeCount += layer->getNodeCount();
  }
  return nodeCount;
}

void NeuralNetwork::train( void ) {
  // for each ( LayerBase* layer in layerList ) {
  //  dMatrix gradient;
  //  layer->train( 0.0, gradient );
  //}
}
