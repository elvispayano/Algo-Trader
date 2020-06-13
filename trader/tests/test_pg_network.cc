/*
  Title:
    PG Network Unit Test

  Description:
    This unit test will call expected SQL functionality and return
    expected values from a test database

  Author:
    Elvis Payano
*/

// Interface Includes
#include "pg_network.h"

// Google Test Includes
#include <gtest/gtest.h>

// Unit Test Framework Setup
class PGNetworkTest :
  public ::testing::Test,
  public PGNetwork {
protected:
  // Ensure each test has a properly configured connection
  // to the postgres database
  void SetUp(void) override {
    setDatabase("dbname = gtest");
    setPort("5431");
    connect();
    ASSERT_EQ(getStatus(), ConnStatusType::CONNECTION_OK);
  }
};

/*
  Test:         Network Count
  Description:
    Ensure expected network count can be retrieved from test
    database
*/
TEST_F(PGNetworkTest, NetworkCount) {
  EXPECT_EQ(2, networkCount());

  disconnect();

  EXPECT_EQ(0, networkCount());
}

/*
  Test:         Get Networks
  Description:
    Ensure that the sql connection returns the expected network data from
    the database
*/
TEST_F(PGNetworkTest, GetNetwork) {
  // Requesting valid data
  EXPECT_STREQ("MSFT", getNetwork(1));

  // Requesting invalid data
  EXPECT_EQ(NULL, getNetwork(0));

  // Requesting with invlid connection
  disconnect();
  EXPECT_EQ(NULL, getNetwork(1));
}

/*
  Test:         Expected Layers
  Description:
    Ensure that the sql connection returns the expected layer count from the
    database
*/
TEST_F(PGNetworkTest, LayerCount) {
  // Requesting valid data
  EXPECT_EQ(3, layerCount("MSFT"));

  // Requesting invalid data
  EXPECT_EQ(0, layerCount("XYZ"));

  // Requesting with invalid connection
  disconnect();
  EXPECT_EQ(0, layerCount("MSFT"));
}
