/*
  Title:
    PG Network

  Description:
    This class is responsible for housing all functionality layers table
    within the postgres databse. Additionally, it will configure outputs
    and return with expected types.

  Tests:
    test_pg_layer.cc

  Author:
    Elvis Payano
*/

// Interface Includes
#include "pg_layer.h"

PGLayer::PGLayer(void) {
  ticker = NULL;
  layerNum = 0;
}

PGLayer::~PGLayer(void) {

}

LayerConfiguration PGLayer::getLayer(char* ticker, int layerNum) {
  // Configure setting to be used by all get functions
  this->ticker = ticker;
  this->layerNum = layerNum;

  // Prep configuration output
  layerOut.layerHeight = getNodes();
  layerOut.layerWidth = getInputs();
  layerOut.offset = getInd();
  layerOut.Activation = getActivationType();
  layerOut.Layer = getLayerType();

  return layerOut;
}

int PGLayer::getInputs(void) {
  char* out = execFunc("layer_inputs", ticker, layerNum);
  return pg2i(out);
}

int PGLayer::getNodes(void) {
  char* out = execFunc("layer_nodes", ticker, layerNum);
  return pg2i(out);
}

int PGLayer::getInd(void) {
  char* out = execFunc("layer_ind", ticker, layerNum);
  return pg2i(out);
}

LayerTypes PGLayer::getLayerType(void) {
  char* qRet = execFunc("layer_type", ticker, layerNum);
  int val = pg2i(qRet);

  if (val >= static_cast<int>(LayerTypes::UNKNOWN)) {
    return LayerTypes::UNKNOWN;
  }
  return static_cast<LayerTypes>(val);
}

ActivationTypes PGLayer::getActivationType(void) {
  char* qRet = execFunc("layer_activation", ticker, layerNum);
  int val = pg2i(qRet);

  if (val >= static_cast<int>(ActivationTypes::UNKNOWN)) {
    return ActivationTypes::UNKNOWN;
  }
  return static_cast<ActivationTypes>(val);
}