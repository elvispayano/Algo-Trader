/*
  Title:
    Activation Unit Test

  Description:
    This Unit Test will configure the activation layer and
    test the results of the Transfer Functions with controlled
    inputs. Tests will be separated by Transfer Function 
    configuration.

  Author:
    Elvis Payano
*/

// Neural Network Includes
#include "activation.h"

// Google Test Includes
#include <gtest/gtest.h>

// Unit Test Framework Setup
class ActivationTest :
  public ::testing::Test,
  public Activation {
protected:
  // Ensure each tests has the inputs configured with the 
  // expected inputs size and values
  void SetUp(void) override {
    in_pos.Resize(1, 1, 10);
    in_neg.Resize(1, 1,-10);
    in_zer.Resize(1, 1,  0);

    out.Resize(1, 1, 0.0);
  }

public:
  dMatrix in_pos;
  dMatrix in_neg;
  dMatrix in_zer;

  dMatrix out;
};

/*
  Test:          None
  Description:
    Run test using the "None" Transfer Function
*/
TEST_F(ActivationTest, None) {
  setTF(ActivationTypes::LINEAR);

  out = performTF(in_pos);
  EXPECT_DOUBLE_EQ(out(0, 0), 10);

  out = performTF(in_neg);
  EXPECT_DOUBLE_EQ(out(0, 0), -10);

  out = performTF(in_zer);
  EXPECT_DOUBLE_EQ(out(0, 0), 0);
};

/*
  Test:          Binary
  Description:
    Run test using the "Binary" Transfer Function
*/
TEST_F(ActivationTest, Binary) {
  setTF(ActivationTypes::BINARY);

  out = performTF(in_pos);
  EXPECT_DOUBLE_EQ(out(0, 0), 1);

  out = performTF(in_neg);
  EXPECT_DOUBLE_EQ(out(0, 0), 0);

  out = performTF(in_zer);
  EXPECT_DOUBLE_EQ(out(0, 0), 1);
};

/*
  Test:          Rectified Linear Unit
  Description:
    Run test using the "Relu" Transfer Function
*/
TEST_F(ActivationTest, Relu) {
  setTF(ActivationTypes::RELU);

  out = performTF(in_pos);
  EXPECT_DOUBLE_EQ(out(0, 0), 10);

  out = performTF(in_neg);
  EXPECT_DOUBLE_EQ(out(0, 0), 0);

  out = performTF(in_zer);
  EXPECT_DOUBLE_EQ(out(0, 0), 0);
};

/*
  Test:          Sigmoid
  Description:
    Run test using the "Sigmoid" Transfer Function
*/
TEST_F(ActivationTest, Sigmoid) {
  setTF(ActivationTypes::SIGMOID);

  out = performTF(in_pos);
  EXPECT_GT(out(0, 0), 0.999);

  out = performTF(in_neg);
  EXPECT_LT(out(0, 0), 0.001);

  out = performTF(in_zer);
  EXPECT_DOUBLE_EQ(out(0, 0), 0.5);
};

/*
  Test:          Hyperbolic Tangent
  Description:
    Run test using the "tanh" Transfer Function
*/
TEST_F(ActivationTest, TanH) {
  setTF(ActivationTypes::TANH);

  out = performTF(in_pos);
  EXPECT_GT(out(0, 0), 0.999);

  out = performTF(in_neg);
  EXPECT_LT(out(0, 0),-0.999);

  out = performTF(in_zer);
  EXPECT_DOUBLE_EQ(out(0, 0), 0);
};
