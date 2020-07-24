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
    nn = new NeuralNetwork(ticker);

    trader = new Trader(broker, db, &networks);
  }

  // Memory Cleanup
  void TearDown(void) override {
    if (trader)
      delete trader;

    if (db)
      delete db;

    if (trader)
      delete trader;

    if (nn)
      delete nn;
  }

public:
  DatabaseBase* db;
  BrokerBase* broker;
  Trader* trader;
  NeuralNetwork* nn;

  std::vector<NeuralNetwork*> networks;

  std::string ticker = "XYZ";
};

