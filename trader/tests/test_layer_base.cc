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
#include <gtest/gtest.h>

// Unit Test Framework Setup
class LayerBaseTest :
  public ::testing::Test,
  public LayerBase {
protected:
  dMatrix processLayer(dMatrix input) override {
    dMatrix output;
    return output;
  };
  
};

TEST_F(LayerBaseTest, Contructor) {
  dMatrix weight = getWeight();
  EXPECT_EQ(1, weight.cols());
  EXPECT_EQ(1, weight.rows());

  dMatrix bias = getBias();
  EXPECT_EQ(1, bias.cols());
  EXPECT_EQ(1, bias.rows());

  EXPECT_EQ(0, getInputCount());
  EXPECT_EQ(0, getNodeCount());
}

TEST_F(LayerBaseTest, Reconfigure) {
  setInputCount(3);
  setNodeCount(2);
  reconfigure();

  EXPECT_EQ(3, getInputCount());
  EXPECT_EQ(2, getNodeCount());
}