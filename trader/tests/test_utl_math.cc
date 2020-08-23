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

class MathTest : public ::testing::Test {
protected:
  // Ensure each test has the inputs configured
  void SetUp( void ) override { rng = new RandomNumber(); }

  void TearDown( void ) override {
    if ( rng )
      delete rng;
  }

public:
  RandomNumber* rng;
};

/*
  Test:         htan
  Description:
    Hyperbolic Tangent Transfer Function
*/
TEST_F( MathTest, HyperbolicTangent ) {
  double temp = rng->random();
  EXPECT_GT( Math::htan( rng->random( 0, 10 ) ), 0.0 );
  EXPECT_LE( Math::htan( rng->random( 0, 10 ) ), 1.0 );

  EXPECT_LT( Math::htan( rng->random( -10, 0 ) ), 0.0 );
  EXPECT_GE( Math::htan( rng->random( -10, 0 ) ), -1.0 );
};

TEST_F( MathTest, HyperbolicTangentDerivative ) {
  EXPECT_GE( Math::htan_d( rng->random( -10, 10 ) ), 0.0 );
  EXPECT_LT( Math::htan_d( rng->random( -10, 10 ) ), 1.0 );
}

/*
  Test:         sigmoid
  Description:
    Sigmoid Transfer Function
*/
TEST_F( MathTest, Sigmoid ) {
  EXPECT_GT( Math::sigmoid( rng->random( 0, 10 ) ), 0.5 );
  EXPECT_LE( Math::sigmoid( rng->random( 0, 10 ) ), 1.0 );

  EXPECT_LT( Math::sigmoid( rng->random( -10, 0 ) ), 0.5 );
  EXPECT_GE( Math::sigmoid( rng->random( -10, 0 ) ), 0.0 );
};

TEST_F( MathTest, SigmoidDerivative ) {
  EXPECT_GE( Math::sigmoid_d( rng->random( -10, 10 ) ), 0.0 );
  EXPECT_LT( Math::sigmoid_d( rng->random( -10, 10 ) ), 1.0 );
}

/*
  Test:         relu & relu derivative
  Description:
    Rectified Linear Unit Transfer Function
*/
TEST_F( MathTest, ReLu ) {
  double input = rng->random( 0, 10 );
  EXPECT_DOUBLE_EQ( input, Math::relu( input ) );
  EXPECT_DOUBLE_EQ( 0.0, Math::relu( rng->random( -10, 0 ) ) );
};

TEST_F( MathTest, ReLuDerivative ) {
  EXPECT_DOUBLE_EQ( 0.0, Math::relu_d( rng->random( -10, 0 ) ) );
  EXPECT_DOUBLE_EQ( 1.0, Math::relu_d( rng->random( 0, 10 ) ) );
}

/*
  Test:         binary & binary derivative
  Description:
    Binary Transfer Function
*/
TEST_F( MathTest, Binary ) {
  EXPECT_DOUBLE_EQ( 1.0, Math::binary( rng->random( 0, 10 ) ) );
  EXPECT_DOUBLE_EQ( 0.0, Math::binary( rng->random( -10, 0 ) ) );
};

TEST_F( MathTest, BinaryDerivative ) {
  EXPECT_DOUBLE_EQ( 0.0, Math::binary_d( rng->random( -10, 10 ) ) );
  EXPECT_DOUBLE_EQ( 1.0, Math::binary_d( 0.0 ) );
}

/*
  Test:         linear & linear derivative
  Description:
    Linear Transfer Function
*/
TEST_F( MathTest, Linear ) {
  double input = rng->random( -10, 10 );
  EXPECT_DOUBLE_EQ( input, Math::linear( input ) );
};

TEST_F( MathTest, LinearDerivative ) {
  EXPECT_DOUBLE_EQ( 1, Math::linear_d( rng->random( -10, 10 ) ) );
}
