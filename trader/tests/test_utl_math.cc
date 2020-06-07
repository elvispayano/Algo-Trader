/*
  Title:
    Utl Math Unit Test

  Description:
    This unit test will test the output of the functions
    creating in the util math library. Tests will be seperated
    by function

  Author:
    Elvis Payano
*/


// Utility Includes
#include "utl_math.h"

// Google Test Includes
#include <gtest/gtest.h>

/*
  Test:         htan
  Description:
    Hyperbolic Tangent Transfer Function
*/
TEST(MathTest, HyperbolicTangent) {
  // Double
  EXPECT_GT(0.999, htan(10.0));
  EXPECT_LT(-0.999, htan(-10.0));

  // Integer
  EXPECT_EQ(0, htan(0));
};

/*
  Test:         sigmoid
  Description:
    Sigmoid Transfer Function
*/
TEST(MathTest, Sigmoid) {
  // Double
  EXPECT_GT(0.999, sigmoid( 10.0));
  EXPECT_LT(0.001, sigmoid(-10.0));
  EXPECT_DOUBLE_EQ(0.5, sigmoid(0.0));
};

/*
  Test:         relu
  Description:
    Rectified Linear Unit Transfer Function
*/
TEST(MathTest, ReLu) {
  // Double
  EXPECT_DOUBLE_EQ(10.0, relu( 10.0));
  EXPECT_DOUBLE_EQ( 0.0, relu(-10.0));

  // Integer
  EXPECT_EQ(0, relu(0));
};

/*
  Test:         binary
  Description:
    Binary Transfer Function
*/
TEST(MathTest, Binary) {
  // Double
  EXPECT_DOUBLE_EQ(1.0, binary( 10.0));
  EXPECT_DOUBLE_EQ(0.0, binary(-10.0));

  // Integer
  EXPECT_EQ(1, binary(0));
};

/*
  Test:         linear
  Description:
    Linear Transfer Function
*/
TEST(MathTest, Linear) {
  // Double
  EXPECT_DOUBLE_EQ( 10.0, linear( 10.0));
  EXPECT_DOUBLE_EQ(-10.0, linear(-10.0));

  // Integer
  EXPECT_EQ(0, linear(0));
};