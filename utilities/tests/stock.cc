/*
  Title:
    Stock Unit Test

  Description:
    This unit test will test the Stock data class implementation to ensure
    expected functionality

  Author:
    Elvis Payano
*/

// Utility Includes
#include "utilities/stock.h"

// Google Test Includes
#include <gtest/gtest.h>

// Unit test framework setup
class StockTest : public ::testing::Test {
protected:
  void SetUp( void ) override { data = new Stock(); }

  void TearDown( void ) override {
    if ( data )
      delete data;
  }

public:
  Stock* data;
};

/*
  Test:         Completion Status
  Description:
    Ensure that all required data has been captured
    before marking the set as completed
*/
TEST_F( StockTest, CompletionStatus ) {
  data->setBid( 5.1f );
  EXPECT_FALSE( data->isComplete() );

  data->setAsk( 5.1f );
  EXPECT_FALSE( data->isComplete() );

  data->setLow( 5.1f );
  EXPECT_FALSE( data->isComplete() );

  data->setHigh( 5.1f );
  EXPECT_TRUE( data->isComplete() );

  data->reset();

  data->setHigh( 5.1f );
  EXPECT_FALSE( data->isComplete() );

  data->setAsk( 5.1f );
  EXPECT_FALSE( data->isComplete() );

  data->setBid( 5.1f );
  EXPECT_FALSE( data->isComplete() );

  data->setLow( 5.1f );
  EXPECT_TRUE( data->isComplete() );
}

/*
  Test:         Getter.Setter
  Description:
    Ensure that all getter and setter pairs are properly configured
*/
TEST_F( StockTest, GetterSetter ) {
  data->setBid( 5.1f );
  EXPECT_FLOAT_EQ( 5.1, data->getBid() );

  data->setAsk( 5.2f );
  EXPECT_FLOAT_EQ( 5.2, data->getAsk() );

  data->setLow( 5.3f );
  EXPECT_FLOAT_EQ( 5.3, data->getLow() );

  data->setHigh( 5.4f );
  EXPECT_FLOAT_EQ( 5.4, data->getHigh() );
}
