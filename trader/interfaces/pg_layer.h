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
#include "pg_connect.h"

// Utility Includes
#include "network_types.h"

class PGLayer : public PGConnect {
public:
  // Constructor
  PGLayer(void);

  // Destructor
  ~PGLayer(void);

  // Layer SQL Interface
  LayerConfiguration getLayer(char* ticker, int layerNum);

protected:
  // Layer SQL Interface
  int getInputs(void);
  int getNodes(void);
  int getInd(void);
  LayerTypes getLayerType(void);
  ActivationTypes getActivationType(void);

private:
  LayerConfiguration layerOut;
  char* ticker;
  int layerNum;
};
