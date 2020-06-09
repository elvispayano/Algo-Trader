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
#include "neural_network.h"
#include "network_types.h"

// Google Test Includes
#include "gtest/gtest.h"

// Unit test framework setup
class NeuralNetworkTest : public ::testing::Test {
protected:
  void SetUp(void) override {
    config.Activation  = ActivationTypes::SIGMOID;
    config.Layer       = LayerTypes::FULLYCONNECTED;
    config.layerHeight = 3;
    config.layerWidth  = 2;
  }

public:
  NeuralNetwork network;
  LayerConfiguration config;
};

/*
  Test:         Default Contructor
  Description:
    Create a Neural Network object and test default settings
*/
TEST_F(NeuralNetworkTest, ConstructorDefault) {
  // Neural Network should be created with no layers
  EXPECT_EQ(0, network.getLayerCount());
}

/*
  Test:         Add Layer (Known)
  Description:
    Add a known layer to the neural network
*/
TEST_F(NeuralNetworkTest, AddLayersKnown) {
  // Add a known layer type
  network.addLayer(config);
  EXPECT_EQ(1, network.getLayerCount());
}

/*
  Test:         Add Layer (Unknown)
  Description:
    Add a unknown layer to the neural network
*/
TEST_F(NeuralNetworkTest, AddLayersUnknown) {
  // Reject an unknown layer type
  config.Layer = LayerTypes::UNKNOWN;
  network.addLayer(config);
  EXPECT_EQ(0, network.getLayerCount());
}
