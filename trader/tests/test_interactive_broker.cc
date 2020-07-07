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

    EXPECT_CALL(*wrapper, connect(host, 6550, 0)).Times(1).WillOnce(::testing::Return(true));
    ASSERT_TRUE(ib->connect());
  }

  void TearDown(void) override {
    EXPECT_CALL(*wrapper, disconnect()).Times(1);
    ib->disconnect();

    if (ib)
      delete ib;
    if (wrapper)
      delete wrapper;
  }

public:
  MockedWrapper* wrapper;
  InteractiveBroker* ib;

  std::string host = "127.0.0.1";
  std::string ticker = "XYZ";
};

/*
  Test:         Connection Management
  Description:
    Ensure that the connection to the IB API is properly handled
*/
TEST_F(InteractiveBrokerTest, ConnectionManagement) {
  // Disconnect
  EXPECT_CALL(*wrapper, disconnect()).Times(1);
  ib->disconnect();

  // Attempt failing connection
  EXPECT_CALL(*wrapper, connect(host, 6550, 0)).Times(3).WillRepeatedly(::testing::Return(false));
  bool isConnected = false;
  EXPECT_THROW(isConnected = ib->connect(), std::runtime_error);
  EXPECT_FALSE(isConnected);

  // Connect
  EXPECT_CALL(*wrapper, connect(host, 6550, 0)).Times(1).WillOnce(::testing::Return(true));
  EXPECT_TRUE(ib->connect());
}

/*
  Test:         Redundant Connections
  Description:
    Properly handle redudant connection attempts
*/
TEST_F(InteractiveBrokerTest, RedundantConnection) {
  EXPECT_TRUE(ib->connect());

  EXPECT_CALL(*wrapper, disconnect()).Times(1);
  ib->disconnect();
  ib->disconnect();

  EXPECT_CALL(*wrapper, connect(host, 6550, 0)).Times(1).WillOnce(::testing::Return(true));
  EXPECT_TRUE(ib->connect());
}