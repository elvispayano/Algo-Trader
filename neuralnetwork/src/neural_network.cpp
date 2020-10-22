/// Neural Network
///
/// This class is responsible for generating and configuring all the neural
/// network layers. This class is also the main interface for the outside
/// implementation.
///
/// \author   Elvis Payano
/// \date     04/09/2020
/// \version  0.0.1

// Neural Network Includes
#include "neuralnetwork/neural_network.h"

// Layer Forward Declaration
#include "neuralnetwork/fully_connected_layer.h"
#include "neuralnetwork/layer_base.h"

//! @fn     NeuralNetwork( void )
//! @brief  Initialize a neural network and layer workspace that will later be
//!         configured.
NeuralNetwork::NeuralNetwork( void ) {
  layerList.clear();
  inputCount  = 0;
  outputCount = 0;

  inputLayer  = 0;
  outputLayer = 0;
  totalLayers = 0;
}

/// @fn     NeuralNetwork( string name, unsigned int layerCount )
/// @param  name        Associated ticker symbol
/// @param  layerCount  Total layers present in network
/// @brief  Initializa a neural network and layer workspace that will later be
///         configured.
NeuralNetwork::NeuralNetwork( std::string name, unsigned int layerCount ) {
  ticker = name;
  layerList.clear();
  totalLayers = layerCount;

  inputCount  = 0;
  outputCount = 0;

  inputLayer  = 0;
  outputLayer = 0;
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

/// @fn     void addLayer( LayerTypes layer, ActivationTypes activation,
///                        unsigned int inputs, unsigned int nodes )
/// @param  layer       Type of layer to create
/// @param  activation  Activation function to use in layer
/// @param  inputs      Number of inputs present in layer
/// @param  nodes       Number of nodes present in layer
/// @brief  Add a new layer to the network. The configuration type contains
///         all the required elements to select the type of layer, implemented
///         activation, and the size of the layer.
void NeuralNetwork::addLayer( LayerTypes      layer,
                              ActivationTypes activation,
                              unsigned int    inputs,
                              unsigned int    nodes ) {

  switch ( layer ) {
  case LayerTypes::FULLYCONNECTED:
    layerList.push_back( new FullyConnectedLayer( activation, inputs, nodes ) );
    printf( "Neural Network: Fully Connected Layer Added\n" );
    break;
  }
}

//! @fn     void addLayer( LayerConfiguration configuration )
//! @brief  Add a new layer to the network. The configuration type contains all
//!         the required elements to select the type of layer, implemented
//!         activation, and the size of the layer.
void NeuralNetwork::addLayer( LayerConfiguration config ) {
  LayerBase* layerCreated = newLayer( config.activation, config.layer );
  if ( !layerCreated )
    return;

  // Layer configuration
  unsigned int inputs =
      ( layerList.size() > 0 ) ? layerList.back()->getNodeCount() : inputCount;

  layerCreated->reconfigure( config.nodes, inputs, config.hyperparams );

  layerList.push_back( layerCreated );
}

//! @fn     void addInputLayer( LayerConfiguration config )
//! @brief  Configure the input layer to the network. The configuration type
//!         contains the required elements to select the type of layer,
//!         implemented activation, and the size of the layer.
void NeuralNetwork::addInputLayer( unsigned int       inputs,
                                   LayerConfiguration config ) {
  inputCount = inputs;
  inputLayer = newLayer( config.activation, config.layer );
  inputLayer->reconfigure( inputs, inputs, config.hyperparams );
}

void NeuralNetwork::addOutputLayer( unsigned int       outputs,
                                    LayerConfiguration config ) {
  outputCount = outputs;
  outputLayer = newLayer( config.activation, config.layer );
  if ( layerList.size() > 0 ) {
    outputLayer->reconfigure(
        outputs, layerList.back()->getNodeCount(), config.hyperparams );
    return;
  }
  outputLayer->reconfigure( outputs, 0, config.hyperparams );
}

LayerBase* NeuralNetwork::newLayer( ActivationTypes activation,
                                    LayerTypes      layer ) {
  LayerBase* layerCreated;
  switch ( layer ) {
  case LayerTypes::FULLYCONNECTED:
    layerCreated = new FullyConnectedLayer( activation );
    break;

  default:
    // LayerTypes::UNKNOWN
    // Unknown layer types are not added to the stack and the return
    // keyword ensures function breaks out and no configuration is
    // attempted
    layerCreated = 0;
  }
  return layerCreated;
}

/// @fn     Matrix process( Matrix data )
/// @brief  Process input data through each layer and return a proccessed matrix
///         containing the desired action to be performed.
Matrix NeuralNetwork::process( Matrix input ) {
  Matrix data = input;

  for ( auto layer : layerList ) {
    data.set( layer->process( data ) );
  }

  return data;
}

//! @fn     unsigned int getTotalNodes( void )
//! @brief  Total nodes used within the network. It is used to determine
//!         approximate complexity.
unsigned int NeuralNetwork::getTotalNodes( void ) {
  unsigned int nodeCount = 0;
  for ( LayerBase* layer : layerList ) {
    nodeCount += layer->getNodeCount();
  }
  return nodeCount;
}

//! @fn     setInputs( unsigned int count )
//! @brief  Set the number of inputs for the neural network
void NeuralNetwork::setInputs( unsigned int count ) {
  inputCount = count;
}

//! @fn     setOutputs( unsigned int count )
//! @brief  Set the number of outputs for the neural network
void NeuralNetwork::setOutputs( unsigned int count ) {
  outputCount = count;
}

void NeuralNetwork::train( void ) {
  // for each ( LayerBase* layer in layerList ) {
  //  Matrix gradient;
  //  layer->train( 0.0, gradient );
  //}
}

/// @fn     bool checkConfiguration( void )
/// @brief  Check if the neural network has been completely configured
bool NeuralNetwork::checkConfiguration( void ) {
  // Check All Layers are present
  if ( !layersAdded() ) {
    return false;
  }

  for ( auto layer : layerList ) {
    if ( !layer->isConfigured() ) {
      return false;
    }
  }
  return true;
}
