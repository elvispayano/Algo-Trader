/*
  Title:
    Neural Network Test

  Description:
    This unit test will create, configure, and operate a neural network
    controller. The tests will be separated by function/feature being tested

  Author:
    Elvis Payano
*/

// Neural Network Includes
#include "neuralnetwork/neural_network.h"

// Utility Includes
#include "utilities/matrix.h"
#include "utilities/network_types.h"
#include "utilities/random_number.h"

// Google Test Includes
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
  unsigned int nodes = 0;
  unsigned int totalLayer = rng.random( 3, 7 );

  for ( size_t iter = 0; iter < totalLayer; ++iter ) {
    LayerConfiguration config = rng.layerConfig();
    nodes += config.nodes;
    network->addLayer( config );
  }

  EXPECT_EQ( totalLayer, network->getLayerCount() );
  EXPECT_EQ( nodes, network->getTotalNodes() );
}
