/*
  Title:
    Activation Unit Test

  Description:
    This unit test will configure the activation layer and
    test the results of the Transfer Functions with controlled
    inputs. Tests will be separated by Transfer Function
    configuration.

  Author:
    Elvis Payano
*/

// Neural Network Includes
#include "activation.h"

// Test Includes
#include "random.h"
#include <gtest/gtest.h>

class ActivationTest : public ::testing::Test {
protected:
  // Ensure each test has the inputs configured
  void SetUp( void ) override {
    activation = new Activation();
    rng        = new RandomNumber();

    input.resize( 2, 3, 0 );
  }

  void TearDown( void ) override {
    if ( activation )
      delete activation;

    if ( rng )
      delete rng;
  }

public:
  Activation*   activation;
  RandomNumber* rng;

  dMatrix input;
};

TEST_F( ActivationTest, Configuration ) {
  ActivationTypes value = rng->activation();
  activation->setTF( value );
  EXPECT_EQ( value, activation->getTF() );
}

TEST_F( ActivationTest, TransferFunction ) {
  activation->setTF( rng->activation() );
  dMatrix output = activation->performTF( input );

  EXPECT_EQ( output.rows(), input.rows() );
  EXPECT_EQ( output.cols(), input.cols() );
}

TEST_F( ActivationTest, Backpropagation ) {
  activation->setTF( rng->activation() );
  dMatrix output = activation->performBP( input );

  EXPECT_EQ( output.rows(), input.rows() );
  EXPECT_EQ( output.cols(), input.cols() );
}
