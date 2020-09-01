//! Network Types
//!
//! A collection of various types that will be used the trader platform to
//! communicated with the Neural Network library. These custom types allow for
//! the trader platform to format requests to the Neural Network in a format
//! that can be consumed.
//!
//! \author   Elvis Payano
//! \date     31/08/2020
//! \version  0.0.1

#ifndef NETWORK_TYPES_H
#define NETWORK_TYPES_H

// Utility Includes
#include "matrix.h"

//! ActivationTypes
//! Collection of potential activation types that can be implemented within a
//! layer in the neural network.
enum class ActivationTypes { LINEAR, BINARY, RELU, TANH, SIGMOID, UNKNOWN };

//! LayerTypes
//! Types of layers that can be created within the neural network
enum class LayerTypes { FULLYCONNECTED, UNKNOWN };

//! LayerConfiguration
//! Message structure holding the desired layer configuration that can be
//! created by the neural network.
struct LayerConfiguration {
  LayerTypes      Layer;        //! Type of layer to create
  ActivationTypes Activation;   //! Activation function to assign within layer
  size_t          layerHeight;  //! Number of nodes present in layer
  size_t          layerWidth;   //! Number of layer inputs
  dMatrix         weight;       //! Layers weight hyperparameters
  dMatrix         bias;         //! Layers bias hyperparameters

  LayerConfiguration()
      : Layer( LayerTypes::UNKNOWN )
      , Activation( ActivationTypes::LINEAR )
      , layerHeight( 0 )
      , layerWidth( 0 ) {}
};

#endif /* NETOWRK_TYPES_H */
