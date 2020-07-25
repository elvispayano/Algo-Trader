/*
  Title:
    Trader Unit Test

  Description:
    This unit test will ensure that the trader is configured with
    expected networks

  Author:
    Elvis Payano
*/

// Trader Includes
#include "trader.h"

// Test Includes
#include "mock_interfaces.h"
#include "mock_matchers.h"
#include "mock_neuralnetwork.h"

// Standard Includes
#include <vector>

// Google Test Includes
#include <gtest/gtest.h>

// Unit Test Framework Setup
class TraderTest : public ::testing::Test {
protected:
  // Ensure each test has a properly mocked database connection
  void SetUp(void) override {
    db     = 0;
    broker = 0;
    trader = 0;
    nn     = 0;

    db = new MockDatabaseBase();
    broker = new MockBrokerBase();
    nn = new MockNeuralNetwork(ticker);

    networks.push_back(nn);
    trader = new Trader(broker, db, &networks);
  }

  // Memory Cleanup
  void TearDown(void) override {
    if (broker) {
      delete broker;
      broker = 0;
    }

    if (db) {
      delete db;
      db = 0;
    }

    if (trader) {
      delete trader;
      trader = 0;
    }

    if (nn) {
      delete nn;
      nn = 0;
    }

    networks.clear();
  }

public:
  MockDatabaseBase* db;
  MockBrokerBase* broker;
  Trader* trader;
  MockNeuralNetwork* nn;

  std::vector<NeuralNetwork*> networks;

  std::string ticker = "XYZ";
};

/*
  Test:         No Update
  Description:
    Expected functionality when no ticker update is present
*/
TEST_F(TraderTest, NoResponse) {
  EXPECT_CALL(*nn, getTicker()).Times(1).WillOnce(::testing::Return(ticker));

  OrderConfig update;
  update.request = Requests::UPDATE;
  update.ticker = ticker;
  EXPECT_CALL(*broker, addToQueue(EqOrderConfig(update))).Times(1);
  EXPECT_CALL(*broker, responseReady(ticker)).Times(1).WillOnce(::testing::Return(false));
  trader->perform();
}

/*
  Test:         Hold Action
  Description:
    Expected functionality when a ticker update is present
    and the neural network requests a hold action
*/
TEST_F(TraderTest, HoldAction) {
  EXPECT_CALL(*nn, getTicker()).Times(1).WillOnce(::testing::Return(ticker));

  OrderConfig update;
  update.request = Requests::UPDATE;
  update.ticker = ticker;
  EXPECT_CALL(*broker, addToQueue(EqOrderConfig(update))).Times(1);
  EXPECT_CALL(*broker, responseReady(ticker)).Times(1).WillOnce(::testing::Return(true));

  Stock response;
  response.setTicker(ticker);
  response.setBid(1);
  response.setAsk(1);
  response.setLow(1);
  response.setHigh(1);
  EXPECT_CALL(*broker, getResponse(ticker)).Times(1).WillOnce(::testing::Return(response));
  
  dMatrix input(4, 1, 1.0);
  dMatrix output(3, 1, 0.0);
  output(1, 0) = 1.0;
  EXPECT_CALL(*nn, process(EqMatrix(input))).Times(1).WillOnce(::testing::Return(output));

  trader->perform();
}

/*
  Test:         Purchase Action
  Description:
    Expected functionality when a ticker update is present
    and the neural network requests a purchase action
*/
TEST_F(TraderTest, PurchaseAction) {
  EXPECT_CALL(*nn, getTicker()).Times(1).WillOnce(::testing::Return(ticker));

  OrderConfig update;
  update.request = Requests::UPDATE;
  update.ticker = ticker;
  EXPECT_CALL(*broker, addToQueue(EqOrderConfig(update))).Times(1);
  EXPECT_CALL(*broker, responseReady(ticker)).Times(1).WillOnce(::testing::Return(true));

  Stock response;
  response.setTicker(ticker);
  response.setBid(1);
  response.setAsk(1);
  response.setLow(1);
  response.setHigh(1);
  EXPECT_CALL(*broker, getResponse(ticker)).Times(1).WillOnce(::testing::Return(response));

  dMatrix input(4, 1, 1.0);
  dMatrix output(3, 1, 0.0);
  output(0, 0) = 1.0;
  EXPECT_CALL(*nn, process(EqMatrix(input))).Times(1).WillOnce(::testing::Return(output));

  OrderConfig request;
  request.ticker = ticker;
  request.request = Requests::MARKET;
  request.purchase = true;
  request.quantity = 1;
  EXPECT_CALL(*broker, addToQueue(EqOrderConfig(request))).Times(1);
  trader->perform();
}

/*
  Test:         Sell Action
  Description:
    Expected functionality when a ticker update is present
    and the neural network requests a sell action
*/
TEST_F(TraderTest, SellAction) {
  EXPECT_CALL(*nn, getTicker()).Times(1).WillOnce(::testing::Return(ticker));

  OrderConfig update;
  update.request = Requests::UPDATE;
  update.ticker = ticker;
  EXPECT_CALL(*broker, addToQueue(EqOrderConfig(update))).Times(1);
  EXPECT_CALL(*broker, responseReady(ticker)).Times(1).WillOnce(::testing::Return(true));

  Stock response;
  response.setTicker(ticker);
  response.setBid(1);
  response.setAsk(1);
  response.setLow(1);
  response.setHigh(1);
  EXPECT_CALL(*broker, getResponse(ticker)).Times(1).WillOnce(::testing::Return(response));

  dMatrix input(4, 1, 1.0);
  dMatrix output(3, 1, 0.0);
  output(2, 0) = 1.0;
  EXPECT_CALL(*nn, process(EqMatrix(input))).Times(1).WillOnce(::testing::Return(output));

  OrderConfig request;
  request.ticker = ticker;
  request.request = Requests::MARKET;
  request.purchase = false;
  request.quantity = 1;
  EXPECT_CALL(*broker, addToQueue(EqOrderConfig(request))).Times(1);
  trader->perform();
}
