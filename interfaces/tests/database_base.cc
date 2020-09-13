/*
  Title:
    Database Base Unit Test

  Description:
    This unit test will test the standard functionality provided to all
    derived database types

  Author:
    Elvis Payano
*/

// Interface Includes
#include "mock_interfaces.h"

// Google Test Includes
#include <gtest/gtest.h>

// Unit test framework setup
class DatabaseTest : public ::testing::Test {
protected:
  void SetUp( void ) override { mDB = new MockDatabaseBase(); }

  void TearDown( void ) override {
    if ( mDB )
      delete mDB;
  }

public:
  DatabaseBase* mDB;
};

/*
  Test:         IntConversion
  Description:
    Ensure input string can be converted into an integer
*/
TEST_F( DatabaseTest, IntConversion ) {
  EXPECT_EQ( 5, mDB->toInt( "5" ) );
}

/*
  Test:         FloatConversion
  Description:
    Ensure input string can be converted into a float
*/
TEST_F( DatabaseTest, FloatConversion ) {
  EXPECT_FLOAT_EQ( 5.5f, mDB->toFloat( "5.5" ) );
}
