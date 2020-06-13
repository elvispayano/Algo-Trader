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
