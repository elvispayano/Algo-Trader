/*
  Title:
    Fully Connected Layer Test

  Description:
    This Unit Test will configure a fully connected layer
    and test data as it is passed through.

  Author:
    Elvis Payano
*/

// Neural Network Includes
#include "fully_connected_layer.h"

// Google Test Includes
#include <gtest/gtest.h>

// Unit Test Framework Setup
class FullyConnectedTest :
  public ::testing::Test,
  public FullyConnectedLayer {
protected:
  // Ensure each tests has the inputs configured with the 
  // expected inputs size and values
  void SetUp(void) override {
    in.Resize(2, 2, 2.0);

    out.Resize(2, 2, 0.0);
  }

public:
  dMatrix in;
  dMatrix out;
};

/*
  Test:
  Description:
*/

TEST_F(FullyConnectedTest, Configuration) {
  setInputCount(10);
  setNodeCount(4);
  
  dMatrix weight_nc = getWeight();
  EXPECT_EQ(0, weight_nc.Cols());
  EXPECT_EQ(0, weight_nc.Rows());

  dMatrix bias_nc = getBias();
  EXPECT_EQ(0, bias_nc.Cols());
  EXPECT_EQ(0, bias_nc.Rows());

  reconfigure();

  dMatrix weight = getWeight();
  EXPECT_EQ(10,weight.Cols());
  EXPECT_EQ(4, weight.Rows());

  dMatrix bias = getBias();
  EXPECT_EQ(1 , bias.Cols());
  EXPECT_EQ(10, bias.Rows());
}