// Neural Network Includes
#include "neuralnetwork/layer_base.h"

// Google Test Includes
#include <gmock/gmock.h>


class MockLayerBase : public LayerBase {
public:
  MockLayerBase( void ) {}
  MOCK_METHOD1( process, dMatrix( dMatrix ) );
  MOCK_METHOD2( train, void( double, dMatrix ) );
  MOCK_METHOD0( getBP, void( void ) );
};
