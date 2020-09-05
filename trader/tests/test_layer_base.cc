/*
  Title:
    Layer Base Test

  Description:
    This unit test will test the implemetation of the layer base
    class

  Author:
    Elvis Payano
*/

// Neural Network Includes
#include "layer_base.h"

// Google Test Includes
#include "mock_matchers.h"
#include "mock_neuralnetwork.h"
#include "random_number.h"
#include <gtest/gtest.h>

// Unit Test Framework Setup
class LayerBaseTest : public ::testing::Test {
protected:
  void SetUp( void ) override {
    mLayer = new MockLayerBase();
    rng    = new RandomNumber();
  }

  void TearDown( void ) override {
    if ( mLayer )
      delete mLayer;

    if ( rng )
      delete rng;
  }

public:
  MockLayerBase* mLayer;
  RandomNumber*  rng;
};

/*
  Test:         Reconfigure
  Description:
    Ensure layer is properly reconfigured as expected
*/
TEST_F( LayerBaseTest, Reconfigure ) {
  int nodes  = (int)rng->random( 1, 5 );
  int inputs = (int)rng->random( 1, 5 );

  unsigned int  totalparams = nodes * inputs + inputs;
  dMatrix hyperparams(totalparams, 1, 0.0 );

  mLayer->reconfigure( nodes, inputs, hyperparams );

  EXPECT_EQ( nodes, mLayer->getNodeCount() );
  EXPECT_EQ( inputs, mLayer->getInputCount() );
}
