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
TEST_F(FullyConnectedTest, ConstructorDefault) {
  dMatrix weight = layer.getWeight();
  EXPECT_EQ(1, weight.cols());
  EXPECT_EQ(1, weight.rows());

  dMatrix bias = layer.getBias();
  EXPECT_EQ(1, bias.cols());
  EXPECT_EQ(1, bias.rows());
}

/*
  Test:         Reconfigure
  Description:
    Reconfigure layer with SetUp settings
*/
TEST_F(FullyConnectedTest, Reconfigure) {
  //reconfigure();

  dMatrix weight = layer.getWeight();
  EXPECT_EQ(10, weight.cols());
  EXPECT_EQ(4 , weight.rows());

  dMatrix bias = layer.getBias();
  EXPECT_EQ(1 , bias.cols());
  EXPECT_EQ(10, bias.rows());
}
