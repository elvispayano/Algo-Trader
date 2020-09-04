/*
  Title:
    Neural Network Test

  Description:
    This unit test will create, configure, and operate a neural network
    controller. The tests will be separated by function/feature being tested

  Author:
    Elvis Payano
*/

// Utility Includes
#include "matrix.h"
#include "network_types.h"
#include "neural_network.h"

// Google Test Includes
#include "random_number.h"
#include <gtest/gtest.h>

// Unit test framework setup
class NeuralNetworkTest : public ::testing::Test {
protected:
  void SetUp( void ) override { network = new NeuralNetwork( "XYZ" ); }

  void TearDown( void ) override {
    if ( network )
      delete network;
  }

public:
  NeuralNetwork* network;
  RandomNumber   rng;
};

//! @test     Add Layer
//! Ensure configured layers are added to the network
TEST_F( NeuralNetworkTest, AddLayer ) {
  LayerConfiguration config = rng.layerConfig();
  unsigned int       nodes  = config.nodes;
  network->addLayer( config );

  EXPECT_EQ( 1, network->getLayerCount() );
  EXPECT_EQ( nodes, network->getTotalNodes() );
}
