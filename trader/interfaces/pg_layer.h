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

// Utility Includes
#include "network_types.h"
#include "matrix.h"

// Forward Declarations
class PGConnect;

class PGLayer {
public:
  // Constructor
  PGLayer(PGConnect* connection);
  PGLayer(void);

  // Destructor
  ~PGLayer(void);

  // Layer SQL Interface
  LayerConfiguration getLayer(char* ticker, int layerNum);

  // Layer SQL Interface
  int getInputs(void);
  int getNodes(void);
  int getInd(void);
  LayerTypes getLayerType(void);
  ActivationTypes getActivationType(void);
  dMatrix getWeight(void);
  dMatrix getBias(void);

private:
  PGConnect* dbConnect;
  LayerConfiguration layerOut;
  char* ticker;
  int layerNum;
};
