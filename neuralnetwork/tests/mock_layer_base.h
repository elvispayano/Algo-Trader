#ifndef MOCK_LAYER_BASE_H
#define MOCK_LAYER_BASE_H

// Neural Network Includes
#include "neuralnetwork/layer_base.h"

// Google Test Includes
#include <gmock/gmock.h>

class MockLayerBase : public LayerBase {
public:
  MockLayerBase( void ) {}
  MOCK_METHOD1( process, Matrix( Matrix ) );
  MOCK_METHOD2( train, void( double, Matrix ) );
  MOCK_METHOD0( getBP, void( void ) );
};

#endif /* MOCK_LAYER_BASE_H */
