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

// Interface Includes
#include "broker_base.h"
#include "database_base.h"

// Util Includes
#include "broker_types.h"
#include "stock.h"

// Google Test Includes
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Standard Includes
#include <vector>
#include <string>

// Google Test Mocked Classes
class MockTraderDB : public  DatabaseBase {
  MOCK_METHOD0(connect, bool(void));
  MOCK_METHOD0(disconnect, void(void));
  MOCK_METHOD0(getNetworkCount, int(void));
  MOCK_METHOD1(getNetwork, std::string(size_t));
  MOCK_METHOD1(getLayerCount, int(std::string));
  MOCK_METHOD2(getLayer, LayerConfiguration(std::string, unsigned int));
};

class MockTraderBroker : public BrokerBase {
  MOCK_METHOD0(connectionManager, void(void));
  MOCK_METHOD0(responseReady, bool(void));
  MOCK_METHOD1(getResponse, void(Stock&));
  MOCK_METHOD1(addToQueue, void(OrderConfig));
};

// Unit Test Framework Setup
class TraderTest : public ::testing::Test {
protected:
  // Ensure each test has a properly mocked database connection
  void SetUp(void) override {
    db     = 0;
    broker = 0;
    trader = 0;

    db = new MockTraderDB();
    broker = new MockTraderBroker();
    //trader = new Trader(db, broker, networks);
  }

  // Memory Cleanup
  void TearDown(void) override {
    if (trader)
      delete trader;

    if (db)
      delete db;

    if (trader)
      delete trader;
  }

public:
  MockTraderDB* db;
  MockTraderBroker* broker;
  Trader* trader;

  std::vector<NeuralNetwork*> networks;
};
//
///*
//  Test:         Network Count
//  Description:
//    Ensure all networks are created
//*/
//TEST_F(TraderTest, NetworkCount) {
//  EXPECT_CALL(*db, getNetworkCount()).Times(2).WillRepeatedly(::testing::Return(1));
//  EXPECT_CALL(*db, getNetwork(1)).Times(1).WillOnce(::testing::Return("XYZ"));
//  EXPECT_CALL(*db, getLayerCount("XYZ")).Times(1).WillOnce(::testing::Return(0));
//  
//  trader->setup();
//  std::vector<NeuralNetwork*> net = trader->getNetworks();
//  
//  EXPECT_EQ(1, net.size());
//}
