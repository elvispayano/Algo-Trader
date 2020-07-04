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

// Google Test Mocked Classes
class MockDatabase : public DatabaseBase {
public:
  MOCK_METHOD0(getNetworkCount, int(void));
  MOCK_METHOD1(getNetwork, std::string(size_t));
  MOCK_METHOD1(getLayerCount, int(std::string));
};

// Unit Test Framework Setup
class TraderTest : public ::testing::Test {
protected:
  // Ensure each test has a properly mocked database connection
  void SetUp(void) override {
    db = new MockDatabase;
    trader = new Trader(db);
  }

  // Memory Cleanup
  void TearDown(void) override {
    if (db)
      delete db;
    if (trader)
      delete trader;
  }

public:
  MockDatabase* db;
  Trader* trader;
};

/*
  Test:         Network Count
  Description:
    Ensure all networks are created
*/
TEST_F(TraderTest, NetworkCount) {
  trader->setup();

  EXPECT_CALL(*db, getNetworkCount()).Times(1).WillOnce(::testing::Return(1));
  EXPECT_CALL(*db, getNetwork(1)).Times(1).WillOnce(::testing::Return("XYZ"));
  EXPECT_CALL(*db, getLayerCount()).Times(1).WillOnce(::testing::Return(0));
  std::vector<NeuralNetwork*> net = trader->getNetworks();
  EXPECT_EQ(1, net.size());
}
