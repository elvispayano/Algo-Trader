/*
  Title:
    PG Connect Unit Test

  Description:
    This unit test will configure a postgres connection and test
    the connection along with handling communication between project
    and the database.

  Author:
    Elvis Payano
*/

// Interface Includes
#include "pg_connect.h"

// Google Test Includes
#include <gtest/gtest.h>

// Unit Test Framework Setup
class PostgresTest :
  public ::testing::Test,
  public PGConnect {
protected:
  // Ensure each test has a properly configured connection to
  // the postgres database
  void SetUp(void) override {
    setDatabase("dbname = gtest");
    setPort("5431");

    EXPECT_EQ(getStatus(), ConnStatusType::CONNECTION_BAD);
  }

};

/*
  Test:         Establish Connection
  Description:
    Ensure a connection can be established
*/
TEST_F(PostgresTest, Connect) {
  connect();
  EXPECT_EQ(getStatus(), ConnStatusType::CONNECTION_OK);
  EXPECT_TRUE(isConnected());
}

/*
  Test:         Establish Failed Connection
  Description:
    Ensure no connection is reported
*/
TEST_F(PostgresTest, FailConnect) {
  setPort("5432");
  connect();
  EXPECT_EQ(getStatus(), ConnStatusType::CONNECTION_BAD);
  EXPECT_FALSE(isConnected());
}

/*
  Test:         Terminate Connection
  Description:
    Ensure a connection can be safely terminated
*/
TEST_F(PostgresTest, Disconnect) {
  connect();
  EXPECT_EQ(getStatus(), ConnStatusType::CONNECTION_OK);
  disconnect();
  EXPECT_EQ(getStatus(), ConnStatusType::CONNECTION_BAD);
}
