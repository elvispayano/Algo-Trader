/*
  Title:
    Network Types

  Description:
    This is a collection of the various enum and struct types
    that are to be used for configuring the neural network and
    will be referenced by various libraries.

  Author:
    Elvis Payano
*/

#ifndef NETWORK_TYPES_H
#define NETWORK_TYPES_H

/*
  Enum:         Activation Types
  Description:
    Enumerated definition type that is used to configure layers
    to use the selected transfer function
*/
enum class ActivationTypes {
  LINEAR,
  BINARY,
  RELU,
  TANH,
  SIGMOID
};

/*
  Enum:         Layer Types
  Description:
    Enumerated definition type that is used to select what type
    of layer to create.
*/
enum class LayerTypes {
  FULLYCONNECTED,
  UNKNOWN
};

/*
  Struct:       Layer Configuration
  Description:
    Combination field that can be used to pass all possible layer
    data needed for creation and configuration
*/
struct LayerConfiguration {
  LayerTypes Layer;
  ActivationTypes Activation;

  LayerConfiguration() :
    Layer(LayerTypes::UNKNOWN),
    Activation(ActivationTypes::LINEAR) {}
};

#endif /* NETOWRK_TYPES_H */
