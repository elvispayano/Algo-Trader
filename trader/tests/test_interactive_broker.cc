/*
  Title:
    Interactive Broker Unit Test

  Description:
    This unit test will test the Interactive Broker implementation of all required 
    broker implementations

  Author:
    Elvis Payano
*/


// Interface Includes
#include "ib_wrapper.h"
#include "interactive_broker.h"

// Google Test Includes
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Google Test Mocked Classes
class MockedWrapper : public IBWrapper {
public:
  MOCK_METHOD3(connect, bool(std::string, int, int));
  MOCK_METHOD0(disconnect, void(void));
};

// Unit test framework setup
class InteractiveBrokerTest : public ::testing::Test {
protected:
  void SetUp(void) override {
    wrapper = new MockedWrapper();
    ib = new InteractiveBroker(wrapper, host, 6550, 0);
  }

  void TearDown(void) override {
    if (ib)
      delete ib;
    if (wrapper)
      delete wrapper;
  }

public:
  MockedWrapper* wrapper;
  InteractiveBroker* ib;

  std::string host = "127.0.0.1";
  bool connected = false;
};

/*
  Test:         Valid Connection
  Description:
    Manage valid connection to Interactive Broker API.
*/
TEST_F(InteractiveBrokerTest, ValidConnection) {
  EXPECT_CALL(*wrapper, connect(host, 6550, 0)).Times(1).WillOnce(::testing::Return(true));
  
  connected = ib->connect();
  
  EXPECT_TRUE(connected);
}

/*
  Test:         Invalid Connection
  Description:
    Manage invalid connection to Interactive Broker API
*/
TEST_F(InteractiveBrokerTest, InvalidConnection) {
  EXPECT_CALL(*wrapper, connect(host, 6550, 0)).Times(3).WillRepeatedly(::testing::Return(false));
  
  EXPECT_THROW(connected = ib->connect(), std::runtime_error);
  
  EXPECT_FALSE(connected);
}

/*
  Test:         Double Connection
  Description:
    Prevent establishing new connection if current connection has already
    been created
*/
TEST_F(InteractiveBrokerTest, DoubleConnection) {
  EXPECT_CALL(*wrapper, connect(host, 6550, 0)).Times(1).WillOnce(::testing::Return(true));
  
  connected = ib->connect();
  connected = ib->connect();
  
  EXPECT_TRUE(connected);
}

/*
  Test:         Safe Disconnection
  Description:
    Safely terminate connection to Interactive Broker API
*/
TEST_F(InteractiveBrokerTest, ValidTermination) {
  ib->disconnect();
  
  EXPECT_CALL(*wrapper, connect(host, 6550, 0)).Times(1).WillOnce(::testing::Return(true));
  ib->connect();
  
  EXPECT_CALL(*wrapper, disconnect()).Times(1);
  ib->disconnect();
}

/*
  Test:         Safe Disconnection
  Description:
    Only terminate if an established connection to the Interactive Broker
    API exists
*/
TEST_F(InteractiveBrokerTest, SingleTermination) {
  EXPECT_CALL(*wrapper, connect(host, 6550, 0)).Times(1).WillOnce(::testing::Return(true));
  ib->connect();
  
  EXPECT_CALL(*wrapper, disconnect()).Times(1);
  ib->disconnect();
  
  ib->disconnect();
}
