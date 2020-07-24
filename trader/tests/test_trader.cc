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
    if (broker)
      delete broker;

    if (db)
      delete db;

    if (trader)
      delete trader;

    for (size_t it = 0; it < networks.size(); ++it)
      if (networks[it])
        delete networks[it];
  }

public:
  MockDatabaseBase* db;
  MockBrokerBase* broker;
  Trader* trader;
  MockNeuralNetwork* nn;

  std::vector<NeuralNetwork*> networks;

  std::string ticker = "XYZ";
};

TEST_F(TraderTest, Response) {
  EXPECT_CALL(*nn, getTicker()).Times(1).WillOnce(::testing::Return(ticker));

  OrderConfig order;
  order.request = Requests::UPDATE;
  order.ticker = ticker;
  EXPECT_CALL(*broker, addToQueue(::testing::Field(&OrderConfig::ticker, ticker))).Times(1);
  EXPECT_CALL(*broker, responseReady(ticker)).Times(1).WillOnce(::testing::Return(true));

  Stock response;
  //EXPECT_CALL(*broker, getResponse(::testing::Field(&Stock::getTicker(), ticker))).Times(1);
  trader->perform();
}

TEST_F(TraderTest, NoResponse) {
  EXPECT_CALL(*nn, getTicker()).Times(1).WillOnce(::testing::Return(ticker));

  OrderConfig order;
  order.request = Requests::UPDATE;
  order.ticker = ticker;
  EXPECT_CALL(*broker, addToQueue(::testing::Field(&OrderConfig::ticker, ticker))).Times(1);
  EXPECT_CALL(*broker, responseReady(ticker)).Times(1).WillOnce(::testing::Return(false));
  trader->perform();
}
