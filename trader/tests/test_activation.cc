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

// Google Test Includes
#include <gtest/gtest.h>

// Unit Test Framework Setup
class ActivationTestOld
    : public ::testing::Test
    , public Activation {
protected:
  // Ensure each tests has the inputs configured with the
  // expected inputs size and values
  void SetUp( void ) override { setTF( ActivationTypes::LINEAR ); }

public:
};

/*
  Test:         Configuration
  Description:
    Set layer configuration and check its value
*/
TEST_F( ActivationTestOld, Configuration ) {
  EXPECT_EQ( ActivationTypes::LINEAR, tfType );
}

// Utility Includes
#include "network_types.h"

// Test Includes
#include "random.h"

class ActivationTest : public ::testing::Test {
protected:
  // Ensure each test has the inputs configured
  void SetUp( void ) override {
    activation = new Activation();
    rng        = new RandomNumber();
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
};

TEST_F( ActivationTest, Configuration ) {
  ActivationTypes value = rng->activation();
  activation->setTF( value );
  EXPECT_EQ( value, activation->getTF() );
}
