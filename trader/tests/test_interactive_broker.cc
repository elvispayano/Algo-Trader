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
  Test:         Single Connection/Termination
  Description:
    Manage valid connection prodcedure to Interactive Broker API. Establish and
    terminate a single connection
*/
TEST_F(InteractiveBrokerTest, SingleConnection) {
  EXPECT_CALL(*wrapper, connect(host, 6550, 0)).Times(1).WillOnce(::testing::Return(true));
  EXPECT_CALL(*wrapper, disconnect()).Times(1);
  
  connected = ib->connect();
  ib->disconnect();
  
  EXPECT_TRUE(connected);
}

/*
  Test:         Double Connection/Termination
  Description:
    Prevent establishing or terminating multiple connections
*/
TEST_F(InteractiveBrokerTest, DoubleConnection) {
  EXPECT_CALL(*wrapper, connect(host, 6550, 0)).Times(1).WillOnce(::testing::Return(true));
  connected = ib->connect();
  connected = ib->connect();
  EXPECT_TRUE(connected);

  EXPECT_CALL(*wrapper, disconnect()).Times(1);
  ib->disconnect();
  ib->disconnect();
}
