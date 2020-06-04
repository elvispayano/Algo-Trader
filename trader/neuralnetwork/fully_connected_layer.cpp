#include "fully_connected_layer.h"

FullyConnectedLayer::FullyConnectedLayer(void) {

}

FullyConnectedLayer::FullyConnectedLayer(ActivationTypes selectTF) {
  setTF(selectTF);
}

FullyConnectedLayer::~FullyConnectedLayer(void) {

}

dMatrix FullyConnectedLayer::processLayer(dMatrix input) {
  dMatrix output;
  return output;
}