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
  layerOut.offset = getInd();
  layerOut.Activation = getActivationType();
  layerOut.Layer = getLayerType();

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
