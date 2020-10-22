//! Fully Connected Layer
//!
//! A layer type in which each node is connected to the previous and
//! next layer. The effects of the output are based on the configured
//! weights and biases.
//!
//! \author   Elvis Payano
//! \date     29/08/2020
//! \version  0.0.1

// Neural Network Includes
#include "neuralnetwork/fully_connected_layer.h"
#include "neuralnetwork/activation.h"

//! @fn     FullyConnectedLayer( void )
//! @brief  An empty constructor that creates the layer with a predefined
//!         (Linear) activation type. If activation type is not set at
//!         initialization it can be set later using the setTF function.
FullyConnectedLayer::FullyConnectedLayer( void )
    : LayerBase( ActivationTypes::LINEAR ) {
  weight.reset( 0.0 );
  bias.reset( 0.0 );

  outputs.reset( 0.0 );
  intermediate.reset( 0.0 );
  inputs.reset( 0.0 );
}

//! @fn     FullyConnectedLayer( ActivationTypes )
//! @param  selectTF    ActivationTypes to be utilized in the layer
//! @brief  Create the layer with the provided activation type. selectTF can
//!         be reset at anytime using the setTF function.
FullyConnectedLayer::FullyConnectedLayer( ActivationTypes selectTF )
    : LayerBase( selectTF ) {
  weight.reset( 0.0 );
  bias.reset( 0.0 );

  outputs.reset( 0.0 );
  intermediate.reset( 0.0 );
  inputs.reset( 0.0 );
}

/// @fn     FullConnectedLayer( ActivationTypes activation, unsigned int
///                             inputs, unsigned int nodes )
/// @param  activation
/// @param  inputs
/// @param  nodes
/// @brief  Create the layer with the provided activation type, and configure
/// the weight and biases appropriate for the expected inputs and nodes.
FullyConnectedLayer::FullyConnectedLayer( ActivationTypes activation,
                                          unsigned int    inputs,
                                          unsigned int    nodes ) {
  weight.resize( nodes, inputs, 0.0 );
  bias.resize( nodes, 1, 0.0 );
}

//! @fn     ~FullyConnectedLayer( void )
//! @brief  Clear any memory allocated in this layer.
FullyConnectedLayer::~FullyConnectedLayer( void ) {}

//! @fn     Matrix process( Matrix input)
//!         Perform the forward propagation functionality through the layer and
//!         generate an output that can be fed to the preceding layer. Applying
//!         the following function:
//!           f(x) =  tf([weight]*[input] + bias)
//!         where f(x) is a matrix and tf is the configured transfer function.
Matrix FullyConnectedLayer::process( Matrix inputs ) {
  this->inputs = inputs;
  intermediate = weight * inputs + bias;
  outputs      = pActivation->performTF( intermediate );
  return outputs;
}

//! @fn     void reconfigure( size_t nodes,
//!                           size_t inputs,
//!                           Matrix hyperparams )
//! @param  nodes       Number of nodes present in layer
//! @param  inputs      Number of inputs present in layer
//! @param  hyperparam  Matrix of hyperparameters containing all weight and
//!                     bias values
//! @brief  Update the layer with the provided hyperparameters that define the
//!         required configuration of the layer
void FullyConnectedLayer::reconfigure( size_t nodes,
                                       size_t inputs,
                                       Matrix hyperparams ) {
  LayerBase::reconfigure( nodes, inputs, hyperparams );

  weight.resize( nodes, inputs, 0.0 );
  bias.resize( nodes, 1, 0.0 );

  outputs.resize( nodes, 1, 0.0 );
  intermediate.resize( nodes, 1, 0.0 );
  this->inputs.resize( inputs, 1, 0.0 );
}

//! @fn     void train( double learnRate, Matrix gradient)
//! @param  learnRate   Measurement of how much to adjust hyperparameters in
//! response to gradient
//! @param  gradient    Description of how to modify hyperparameters in response
//! to training error
//! @brief  Run the training algorithm on this layer using the backpropagation
//!         gradient calculated from all preceding layers. Applying the
//!         following function:
//!           weight = weight - learnRate * gradient
void FullyConnectedLayer::train( double learnRate, Matrix gradient ) {
  // Generate FC Layers
  dIntdIn  = inputs;
  dOutdInt = pActivation->performBP( intermediate );

  weight -= gradient * learnRate;
}

/// @fn     void configure( unsigned int index, float value )
/// @param  index
/// @param  value
/// @brief  Apply hyperparameters to layer
void FullyConnectedLayer::configure( unsigned int index, float value ) {}
