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
#include "broker_types.h"
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
  MOCK_METHOD1(getCurrentPrice, void(std::string));
  MOCK_METHOD0(processMessages, void(void));
};

// Unit test framework setup
class InteractiveBrokerTest : public ::testing::Test {
protected:
  void SetUp(void) override {
    wrapper = new MockedWrapper(host, 6550, 0);
    ib = new InteractiveBroker(wrapper);

    request.setAction(Requests::UPDATE);
    request.setTicker(ticker);
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
  Stock request;

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
  EXPECT_CALL(*wrapper, connect()).Times(2).WillRepeatedly(::testing::Return(true));
  EXPECT_CALL(*wrapper, disconnect()).Times(1);
  
  EXPECT_CALL(*wrapper, getCurrentPrice(ticker)).Times(1);
  EXPECT_CALL(*wrapper, processMessages()).Times(1);
  
  ib->addMessage(request);
  ib->connectionManager();
  Sleep(60);
}
