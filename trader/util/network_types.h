#ifndef NETWORK_TYPES_H
#define NETWORK_TYPES_H

enum class ActivationTypes {
  LINEAR,
  BINARY,
  RELU,
  TANH,
  SIGMOID
};

enum class LayerTypes {
  FULLYCONNECTED,
  UNKNOWN
};

struct LayerConfiguration {
  LayerTypes Layer;
  ActivationTypes Activation;

  LayerConfiguration() :
    Layer(LayerTypes::FULLYCONNECTED),
    Activation(ActivationTypes::LINEAR) {}
};

#endif /* NETOWRK_TYPES_H */
