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
#include "neuralnetwork/layer_base.h"

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
  unsigned int nodes        = 0;
  unsigned int hiddenLayers = rng.random( 3, 7 );

  for ( size_t iter = 0; iter < hiddenLayers; ++iter ) {
    LayerConfiguration config = rng.layerConfig();
    nodes += config.nodes;
    network->addLayer( config );
  }

  EXPECT_EQ( hiddenLayers, network->getLayerCount() );
  EXPECT_EQ( nodes, network->getTotalNodes() );
}

TEST_F( NeuralNetworkTest, InputLayer ) {
  unsigned int       inputs = rng.random( 3, 10 );
  LayerConfiguration config = rng.layerConfig();
  network->addInputLayer( inputs, config );

  LayerConfiguration hiddenLayerConfig = rng.layerConfig();
  network->addLayer( hiddenLayerConfig );

  LayerBase* inputLayer = network->getInputLayer();
  EXPECT_EQ( inputs, inputLayer->getInputCount() );

  EXPECT_EQ( network->getInputLayer()->getNodeCount(),
             network->getLayer( 1 )->getInputCount() );
}

TEST_F( NeuralNetworkTest, OutputLayer ) {
  unsigned int       outputs = rng.random( 3, 10 );
  LayerConfiguration config  = rng.layerConfig();

  network->addOutputLayer( outputs, config );

  EXPECT_EQ( outputs, network->getOutputLayer()->getNodeCount() );
}
