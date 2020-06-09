/*
  Title:
    Fully Connected Layer Test

  Description:
    This unit test will configure a fully connected layer
    and test data as it is passed through.

  Author:
    Elvis Payano
*/

// Neural Network Includes
#include "fully_connected_layer.h"

// Google Test Includes
#include <gtest/gtest.h>

// Unit Test Framework Setup
class FullyConnectedTest : public ::testing::Test {
protected:
  // Ensure each tests has the inputs configured with the 
  // expected inputs size and values
  void SetUp(void) override {
    layer.setInputCount(10);
    layer.setNodeCount(4);
  }

public:
  FullyConnectedLayer layer;
};

/*
  Test:         Constructor Default
  Description:
    Create layer with default constructor
*/
TEST_F(FullyConnectedTest, ProcessLayer) {
  layer.setTF(ActivationTypes::SIGMOID);

  dMatrix input(4, 10, 0.0);
  dMatrix output = layer.processLayer(input);

  EXPECT_DOUBLE_EQ(0.5, output(0, 0));
}