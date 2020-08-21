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
#include "random.h"
#include <gtest/gtest.h>

/*
  Test:         htan
  Description:
    Hyperbolic Tangent Transfer Function
*/
TEST( MathTest, HyperbolicTangent ) {
  EXPECT_GT( htan( random_p() ), 0.0 );
  EXPECT_LE( htan( random_p() ), 1.0 );

  EXPECT_LT( htan( random_n() ), 0.0 );
  EXPECT_GE( htan( random_n() ), -1.0 );
};

/*
  Test:         sigmoid
  Description:
    Sigmoid Transfer Function
*/
TEST( MathTest, Sigmoid ) {
  EXPECT_GT( sigmoid( random_p() ), 0.5 );
  EXPECT_LE( sigmoid( random_p() ), 1.0 );

  EXPECT_LT( sigmoid( random_n() ), 0.5 );
  EXPECT_GE( sigmoid( random_n() ), 0.0 );
};

/*
  Test:         relu & relu derivative
  Description:
    Rectified Linear Unit Transfer Function
*/
TEST( MathTest, ReLu ) {
  double input = random_p();
  EXPECT_DOUBLE_EQ( input, relu( input ) );
  EXPECT_DOUBLE_EQ( 0.0, relu( random_n() ) );
};

TEST( MathTest, ReLuDerivative ) {
  EXPECT_DOUBLE_EQ( 0.0, relu_d( random_n() ) );
  EXPECT_DOUBLE_EQ( 1.0, relu_d( random_p() ) );
}

/*
  Test:         binary & binary derivative
  Description:
    Binary Transfer Function
*/
TEST( MathTest, Binary ) {
  EXPECT_DOUBLE_EQ( 1.0, binary( random_p() ) );
  EXPECT_DOUBLE_EQ( 0.0, binary( random_n() ) );
};

TEST( MathTest, BinaryDerivative ) {
  EXPECT_DOUBLE_EQ( 0.0, binary_d( random() ) );
  EXPECT_DOUBLE_EQ( 1.0, binary_d( 0.0 ) );
}

/*
  Test:         linear & linear derivative
  Description:
    Linear Transfer Function
*/
TEST( MathTest, Linear ) {
  double input = random();
  EXPECT_DOUBLE_EQ( input, linear( input ) );
};

TEST( MathTest, LinearDerivative ) {
  EXPECT_DOUBLE_EQ( 1, linear_d( random() ) );
}
