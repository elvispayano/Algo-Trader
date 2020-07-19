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
#include "database_base.h"

// Google Test Includes
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Standard Includes
#include <vector>
#include <string>

// Forward Declaration
struct LayerConfiguration;

// Google Test Mocked Classes
class MockTraderDB : public DatabaseBase {
public:
  MOCK_METHOD0(getNetworkCount, int());
  MOCK_METHOD1(getNetwork, std::string(size_t));
  MOCK_METHOD1(getLayerCount, int(std::string));

  bool connect(void) override { return false; }
  void disconnect(void) override {}
  LayerConfiguration getLayer(std::string ticker, unsigned int layerNum) { return temp; }

private:
  LayerConfiguration temp;
};

// Unit Test Framework Setup
//class TraderTest : public ::testing::Test {
//protected:
//  // Ensure each test has a properly mocked database connection
//  void SetUp(void) override {
//    db = new MockTraderDB;
//    trader = new Trader(db);
//  }
//
//  // Memory Cleanup
//  void TearDown(void) override {
//    if (trader)
//      delete trader;
//
//    if (db)
//      delete db;
//  }
//
//public:
//  MockTraderDB* db;
//  Trader* trader;
//};
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
