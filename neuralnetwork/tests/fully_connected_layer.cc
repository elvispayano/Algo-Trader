/*
  Title:
    Fully Connected Layer Test

  Description:
    This unit test will test the implemetation of the fully connected layer

  Author:
    Elvis Payano
*/

// Neural Network Includes
#include "neuralnetwork/fully_connected_layer.h"

// Utility Includes
#include "utilities/random_number.h"

// Google Test Includes
#include <gtest/gtest.h>

// Unit Test Framework Setup
class FullyConnectedLayerTest : public ::testing::Test {
protected:
  void SetUp( void ) override {
    rng = new RandomNumber();
    fc  = new FullyConnectedLayer();

    int nodes  = (int)rng->random( 1, 5 );
    int inputs = (int)rng->random( 1, 5 );

    Matrix weight( nodes, inputs, 0.0 );
    Matrix bias( nodes, 1, 0.0 );

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
  Matrix input( fc->getInputCount(), 1, 0.0 );
  input.randomize();

  Matrix output = fc->process( input );

  EXPECT_EQ( output.rows(), fc->getNodeCount() );
  EXPECT_EQ( output.cols(), 1 );
}
