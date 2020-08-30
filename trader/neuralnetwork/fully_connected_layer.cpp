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
#include "fully_connected_layer.h"
#include "activation.h"

//! @fn     FullyConnectedLayer( void )
//! @brief  An empty constructor that creates the layer with a predefined
//! (Linear)
//!         activation type. If activation type is not set at initialization it
//!         can be set later using the setTF function.
FullyConnectedLayer::FullyConnectedLayer( void )
    : LayerBase( ActivationTypes::LINEAR ) {}

//! @fn     FullyConnectedLayer( ActivationTypes )
//! @param  selectTF    ActivationTypes to be utilized in the layer
//! @brief  Create the layer with the provided activation type. selectTF can
//!         be reset at anytime using the setTF function.
FullyConnectedLayer::FullyConnectedLayer( ActivationTypes selectTF )
    : LayerBase( selectTF ) {}

//! @fn     ~FullyConnectedLayer( void )
//! @brief  Clear any memory allocated in this layer.
FullyConnectedLayer::~FullyConnectedLayer( void ) {}

//! @fn     dMatrix process( dMatrix input)
//!         Perform the forward propagation functionality through the layer and
//!         generate an output that can be fed to the preceding layer. Applying
//!         the following function:
//!           f(x) =  tf([weight]*[input] + bias)
//!         where f(x) is a matrix and tf is the configured transfer function.
dMatrix FullyConnectedLayer::process( dMatrix inputs ) {
  this->inputs = inputs;
  intermediate = weight * inputs + bias;
  outputs      = pActivation->performTF( intermediate );
  return outputs;
}

//! @fn     void train( double learnRate, dMatrix gradient)
//! @param  learnRate   Measurement of how much to adjust hyperparameters in
//! response to gradient
//! @param  gradient    Description of how to modify hyperparameters in response
//! to training error
//! @brief  Run the training algorithm on this layer using the backpropagation
//!         gradient calculated from all preceding layers. Applying the
//!         following function:
//!           weight = weight - learnRate * gradient
void FullyConnectedLayer::train( double learnRate, dMatrix gradient ) {
  // Generate FC Layers
  dIntdIn  = inputs;
  dOutdInt = pActivation->performBP( intermediate );

  weight -= gradient * learnRate;
}
