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

// Google Test Includes
#include <gtest/gtest.h>

// Standard Includes
#include <vector>

// Unit Test Framework Setup
class TraderTest :
  public ::testing::Test,
  public Trader {
protected:
  // Ensure each test has a properly configured connection
  // to the postgres database
  void SetUp(void) override {
    pgN->setDatabase("dbname = gtest");
    pgN->setPort("5431");

    pgL->setDatabase("dbname = gtest");
    pgL->setPort("5431");

    ASSERT_EQ(pgN->getStatus(), ConnStatusType::CONNECTION_OK);
    ASSERT_EQ(pgL->getStatus(), ConnStatusType::CONNECTION_OK);
  }
};

/*
  Test:         Network Count
  Description:
    Ensure all networks are created
*/
TEST_F(TraderTest, NetworkCount) {
  setup();

  std::vector<NeuralNetwork*> net = getNetworks();
  EXPECT_EQ(2, net.size());
}
