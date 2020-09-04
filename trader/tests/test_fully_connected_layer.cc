/*
  Title:
    Fully Connected Layer Test

  Description:
    This unit test will test the implemetation of the fully connected layer

  Author:
    Elvis Payano
*/

// Neural Network Includes
#include "fully_connected_layer.h"

// Google Test Includes
#include "random_number.h"
#include <gtest/gtest.h>

// Unit Test Framework Setup
class FullyConnectedLayerTest : public ::testing::Test {
protected:
  void SetUp( void ) override {
    rng = new RandomNumber();
    fc  = new FullyConnectedLayer();

    int nodes  = (int)rng->random( 1, 5 );
    int inputs = (int)rng->random( 1, 5 );

    dMatrix weight( nodes, inputs, 0.0 );
    dMatrix bias( nodes, 1, 0.0 );

    weight.randomize();
    bias.randomize();

    fc->reconfigure( nodes, inputs, weight );
  }

  void TearDown( void ) override {
    if ( fc )
      delete fc;

    if ( rng )
      delete rng;
  }

public:
  FullyConnectedLayer* fc;
  RandomNumber*        rng;
};

TEST_F( FullyConnectedLayerTest, Processing ) {
  dMatrix input( fc->getInputCount(), 1, 0.0 );
  input.randomize();

  dMatrix output = fc->process( input );

  EXPECT_EQ( output.rows(), fc->getNodeCount() );
  EXPECT_EQ( output.cols(), 1 );
}
