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

// Utility Includes
#include "stock.h"

// Google Test Includes
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Google Test Mocked Classes
class MockedWrapper : public IBWrapper {
public:
  MockedWrapper(std::string host, int port, int clientID) : IBWrapper(host, port, clientID) {}
  MOCK_METHOD0(connect, bool(void));
  MOCK_METHOD0(disconnect, void(void));
  MOCK_METHOD1(getCurrentPrice, Stock(std::string));
  MOCK_METHOD0(processMessages, void(void));
};

// Unit test framework setup
class InteractiveBrokerTest : public ::testing::Test {
protected:
  void SetUp(void) override {
    wrapper = new MockedWrapper(host, 6550, 0);
    ib = new InteractiveBroker(wrapper);
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
  std::string ticker = "XYZ";
};

/*
  Test:         Connection Management
  Description:
    Ensure that the connection to the IB API is properly handled
*/
TEST_F(InteractiveBrokerTest, ConnectionManagerException) {
  EXPECT_CALL(*wrapper, connect()).Times(3).WillRepeatedly(::testing::Return(false));
  EXPECT_THROW(ib->connectionManager(), std::runtime_error);
}

TEST_F(InteractiveBrokerTest, ConnectionManager) {
  EXPECT_CALL(*wrapper, connect()).Times(1).WillOnce(::testing::Return(true));
  EXPECT_CALL(*wrapper, disconnect()).Times(1);
  
  Stock out;
  EXPECT_CALL(*wrapper, getCurrentPrice(ticker)).Times(1).WillOnce(::testing::Return(out));
  EXPECT_CALL(*wrapper, processMessages()).Times(1);
  ib->addMessage(1);
  ib->connectionManager();
}