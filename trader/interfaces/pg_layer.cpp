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

/*
  Constructor:  PGLayer
  Inputs:       None (void)

  Description:
    Initialize class variables with default (invalid) values
*/
PGLayer::PGLayer(void) {
  ticker = NULL;
  layerNum = 0;
}

/*
  Destructor: ~PGLayer
  Inputs:     None(void)

  Description:
    Default destructor
*/
PGLayer::~PGLayer(void) {

}

/*
  Function:     getLayer
  Inputs:       ticker (char*), layerNum (int)

  Description:
    Request layer configuration values from the database for a given
    ticker and layer number
*/
LayerConfiguration PGLayer::getLayer(char* ticker, int layerNum) {
  // Configure setting to be used by all get functions
  this->ticker = ticker;
  this->layerNum = layerNum;

  // Prep configuration output
  layerOut.layerHeight = getNodes();
  layerOut.layerWidth = getInputs();
  layerOut.Activation = getActivationType();
  layerOut.Layer = getLayerType();

  // Load weights and biases
  layerOut.weight.resize(getNodes(), getInputs());
  layerOut.weight = getWeight();
  layerOut.bias.resize(getNodes(), 1);
  layerOut.bias = getBias();

  return layerOut;
}

/*
  Function:     getInputs
  Inputs:       None (void)

  Description:
    SQL request specifying how many inputs are present for the layer
*/
int PGLayer::getInputs(void) {
  char* out = execFunc("layer_inputs", ticker, layerNum);
  return pg2i(out);
}

/*
  Function:     getNodes
  Inputs:       None (void)

  Description:
    SQL request specifying how many nodes are present for the layer
*/
int PGLayer::getNodes(void) {
  char* out = execFunc("layer_nodes", ticker, layerNum);
  return pg2i(out);
}

/*
  Function:     getInd
  Inputs:       None (void)

  Description:
    SQL request for specific layer index to mark when to search for
    weight and bias values within the database
*/
int PGLayer::getInd(void) {
  char* out = execFunc("layer_ind", ticker, layerNum);
  return pg2i(out);
}

/*
  Function:     getLayerType
  Inputs:       None (void)

  Description:
    SQL request for the layer type configurations
*/
LayerTypes PGLayer::getLayerType(void) {
  char* qRet = execFunc("layer_type", ticker, layerNum);
  int val = pg2i(qRet);

  if (val >= static_cast<int>(LayerTypes::UNKNOWN)) {
    return LayerTypes::UNKNOWN;
  }
  return static_cast<LayerTypes>(val);
}

/*
  Function:     getActivationType
  Inputs:       None (void)

  Description:
    SQL request for the activation type configurations
*/
ActivationTypes PGLayer::getActivationType(void) {
  char* qRet = execFunc("layer_activation", ticker, layerNum);
  int val = pg2i(qRet);

  if (val >= static_cast<int>(ActivationTypes::UNKNOWN)) {
    return ActivationTypes::UNKNOWN;
  }
  return static_cast<ActivationTypes>(val);
}

/*
  Function:     getWeight
  Inputs:       None (void)

  Description:
    SQL request for all weight values for the layer
*/
dMatrix PGLayer::getWeight(void) {
  dMatrix out(layerOut.layerHeight, layerOut.layerWidth, 0.0);
  int ind = getInd();
  for (size_t c = 0; c < out.cols(); ++c)
    for (size_t r = 0; r < out.rows(); ++r)
      out(r, c) = pg2f(execFunc("get_wb", ticker, ind++));

  return out;
}

/*
  Function:     getBias
  Inputs:       None (void)

  Description:
    SQL request for all bias values for the layer
*/
dMatrix PGLayer::getBias(void) {
  dMatrix out(layerOut.layerHeight, 1, 0.0);
  int ind = getInd() + layerOut.layerHeight*layerOut.layerWidth;
  for (size_t c = 0; c < out.cols(); ++c)
    for (size_t r = 0; r < out.rows(); ++r)
      out(r, c) = pg2f(execFunc("get_wb", ticker, ind++));

  return out;
}
