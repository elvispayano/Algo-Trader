/*
  Title:
    PG Layer Unit Test

  Description:
    This unit test will call expected SQL functionality pertaining to the
    neural network layer configuration and return expected values from a
    test database

  Author:
    Elvis Payano
*/

// Interface Includes
#include "pg_layer.h"

// Google Test Includes
#include <gtest/gtest.h>

// Unit Test Framework Setup
class PGLayerTest :
  public ::testing::Test,
  public PGLayer {
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

TEST_F(PGLayerTest, temp) {
  EXPECT_TRUE(false);
}