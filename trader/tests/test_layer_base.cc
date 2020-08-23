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
#include "mock_neuralnetwork.h"
#include "mock_matchers.h"
#include "random.h"
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

  dMatrix weight( nodes, inputs, 0.0 );
  dMatrix bias( nodes, 1, 0.0 );

  weight.randomize();
  bias.randomize();

  mLayer->reconfigure( nodes, inputs, weight, bias );

  EXPECT_EQ( nodes, mLayer->getNodeCount() );
  EXPECT_EQ( inputs, mLayer->getInputCount() );

  EXPECT_THAT( weight, EqMatrix( mLayer->getWeight() ) );
  EXPECT_THAT( bias, EqMatrix( mLayer->getBias() ) );
}
