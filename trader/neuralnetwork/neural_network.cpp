#include "neural_network.h"
#include "layer_base.h"
#include "fully_connected_layer.h"

NeuralNetwork::NeuralNetwork(void) {
  layers.clear();
}

NeuralNetwork::~NeuralNetwork(void) {
  for (size_t i = 0; i < layers.size(); ++i) {
    delete layers[i];
  }
  layers.clear();
}

void NeuralNetwork::addLayer(LayerConfiguration configuration) {
  switch (configuration.Layer) {
  case LayerTypes::FULLYCONNECTED:
    layers.push_back(new FullyConnectedLayer);
    break;

  default:
    return;
  }
  
  layers.back()->setTF(configuration.Activation);
}