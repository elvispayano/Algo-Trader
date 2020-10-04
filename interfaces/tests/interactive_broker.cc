/*
  Title:
    Interactive Broker Unit Test

  Description:
    This unit test will test the Interactive Broker implementation of all
  required broker implementations

  Author:
    Elvis Payano
*/

// Interface Includes
#include "interactive_broker.h"

// Test Includes
#include "mock_ib_wrapper.h"

// Google Test Includes
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Standard Includes
#include <chrono>
#include <thread>

// Unit test framework setup
class InteractiveBrokerTest : public ::testing::Test {
protected:
  void SetUp( void ) override {
    wrapper = new MockedIBWrapper( host, 6550, 0 );
    ib      = new InteractiveBroker( wrapper );

    message.ticker   = ticker;
    message.quantity = 2;
    message.price    = 50;
    message.purchase = true;
  }

  void TearDown( void ) override {
    if ( ib )
      delete ib;
  }

public:
  MockedIBWrapper*   wrapper;
  InteractiveBroker* ib;

  OrderConfig message;

  std::string host   = "127.0.0.1";
  std::string ticker = "XYZ";
  std::string buy    = "BUY";
  std::string sell   = "SELL";
};

/*
  Test:         Exception
  Description:
    Ensure that an exception is thrown if a connection can not be
    established
*/
TEST_F( InteractiveBrokerTest, Exception ) {
  EXPECT_CALL( *wrapper, connect() )
      .Times( 3 )
      .WillRepeatedly( ::testing::Return( false ) );
  EXPECT_THROW( ib->connectionManager(), std::runtime_error );
}

/*
  Test:         Update Ticker
  Description:
    Ensure that connection manager requests a ticker update from IB
    API
*/
TEST_F( InteractiveBrokerTest, UpdateTicker ) {
  EXPECT_CALL( *wrapper, connect() )
      .Times( 2 )
      .WillRepeatedly( ::testing::Return( true ) );
  EXPECT_CALL( *wrapper, disconnect() ).Times( 1 );
  EXPECT_CALL( *wrapper, getCurrentPrice( ticker ) ).Times( 1 );
  EXPECT_CALL( *wrapper, processMessages() ).Times( 1 );
  EXPECT_CALL( *wrapper, responseReady() )
      .Times( 1 )
      .WillOnce( ::testing::Return( false ) );

  message.request = Requests::UPDATE;
  ib->addToQueue( message );
  ib->connectionManager();

  std::this_thread::sleep_for( std::chrono::milliseconds( 5 ) );
}

/*
  Test:         Market Order
  Description:
    Request a Market Order through the IB API
*/
TEST_F( InteractiveBrokerTest, MarketOrder ) {
  EXPECT_CALL( *wrapper, connect() )
      .Times( 2 )
      .WillRepeatedly( ::testing::Return( true ) );
  EXPECT_CALL( *wrapper, disconnect() ).Times( 1 );
  EXPECT_CALL( *wrapper, processMessages() ).Times( 1 );
  EXPECT_CALL( *wrapper, responseReady() )
      .Times( 1 )
      .WillOnce( ::testing::Return( false ) );

  message.request = Requests::MARKET;
  EXPECT_CALL( *wrapper, orderMarket( message.ticker, buy, message.quantity ) )
      .Times( 1 );

  ib->connectionManager();
  ib->addToQueue( message );
  std::this_thread::sleep_for( std::chrono::milliseconds( 5 ) );
}

/*
  Test:         Limit Order
  Description:
    Request a Limit Order through the IB API
*/
TEST_F( InteractiveBrokerTest, LimitOrder ) {
  EXPECT_CALL( *wrapper, connect() )
      .Times( 2 )
      .WillRepeatedly( ::testing::Return( true ) );
  EXPECT_CALL( *wrapper, disconnect() ).Times( 1 );
  EXPECT_CALL( *wrapper, processMessages() ).Times( 1 );
  EXPECT_CALL( *wrapper, responseReady() )
      .Times( 1 )
      .WillOnce( ::testing::Return( false ) );

  message.request = Requests::LIMIT;
  EXPECT_CALL(
      *wrapper,
      orderLimit( message.ticker, buy, message.quantity, message.price ) )
      .Times( 1 );

  ib->connectionManager();
  ib->addToQueue( message );
  std::this_thread::sleep_for( std::chrono::milliseconds( 5 ) );
}

/*
  Test:         Stop Order
  Description:
    Request a Stop Order through the IB API
*/
TEST_F( InteractiveBrokerTest, StopOrder ) {
  EXPECT_CALL( *wrapper, connect() )
      .Times( 2 )
      .WillRepeatedly( ::testing::Return( true ) );
  EXPECT_CALL( *wrapper, disconnect() ).Times( 1 );
  EXPECT_CALL( *wrapper, processMessages() ).Times( 1 );
  EXPECT_CALL( *wrapper, responseReady() )
      .Times( 1 )
      .WillOnce( ::testing::Return( false ) );

  message.request  = Requests::STOP;
  message.purchase = false;
  EXPECT_CALL(
      *wrapper,
      orderStop( message.ticker, sell, message.quantity, message.price ) )
      .Times( 1 );

  ib->connectionManager();
  ib->addToQueue( message );
  std::this_thread::sleep_for( std::chrono::milliseconds( 5 ) );
}

/*
  Test:         Broker Response
  Description:
    Capture a formatted response from the Broker API
*/
TEST_F( InteractiveBrokerTest, BrokerResponse ) {
  EXPECT_CALL( *wrapper, connect() )
      .Times( 2 )
      .WillRepeatedly( ::testing::Return( true ) );
  EXPECT_CALL( *wrapper, disconnect() ).Times( 1 );
  EXPECT_CALL( *wrapper, processMessages() ).Times( 1 );
  EXPECT_CALL( *wrapper, responseReady() )
      .Times( 1 )
      .WillOnce( ::testing::Return( true ) );

  Stock output1;
  output1.setTicker( ticker );
  output1.setBid( 1 );
  output1.setAsk( 1 );
  output1.setLow( 1 );
  output1.setHigh( 1 );

  EXPECT_CALL( *wrapper, getResponse() )
      .Times( 1 )
      .WillOnce( ::testing::Return( output1 ) );
  ib->connectionManager();
  std::this_thread::sleep_for( std::chrono::milliseconds( 5 ) );

  EXPECT_TRUE( ib->responseReady( ticker ) );

  Stock capture = ib->getResponse( ticker );
  // EXPECT_STREQ(output1.getTicker(), capture.getTicker());
  EXPECT_DOUBLE_EQ( output1.getBid(), capture.getBid() );
  EXPECT_DOUBLE_EQ( output1.getAsk(), capture.getAsk() );
  EXPECT_DOUBLE_EQ( output1.getLow(), capture.getLow() );
  EXPECT_DOUBLE_EQ( output1.getHigh(), capture.getHigh() );

  EXPECT_FALSE( ib->responseReady( ticker ) );

  output1.reset();
  capture = ib->getResponse( ticker );
  EXPECT_DOUBLE_EQ( output1.getBid(), capture.getBid() );
  EXPECT_DOUBLE_EQ( output1.getAsk(), capture.getAsk() );
  EXPECT_DOUBLE_EQ( output1.getLow(), capture.getLow() );
  EXPECT_DOUBLE_EQ( output1.getHigh(), capture.getHigh() );
}

int main( int argc, char** argv ) {
  testing::InitGoogleTest( &argc, argv );

  return RUN_ALL_TESTS();
}