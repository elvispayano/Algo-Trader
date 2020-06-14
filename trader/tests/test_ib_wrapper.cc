/*
  Title:
    IB Wrapper Unit Test

  Description:
    This unit test will configure the interactive broker connection
    and test the communication between the project and the TWS platform

  Author:
    Elvis Payano
*/

// Interface Includes
#include "ib_wrapper.h"

// Google Test Includes
#include <gtest/gtest.h>

//Unit test framework setup
class IBWrapperTest :
  public ::testing::Test,
  public IBWrapper {
protected:
  // Ensure each test has a properly configured connection to the
  // TWS platform
  void SetUp(void) override {
    connect("127.0.0.1", 6550, 0);
    ASSERT_TRUE(isConnected());
  }

  void TearDown(void) override {
    disconnect();
  }
};

TEST_F(IBWrapperTest, Connection) {
  SUCCEED();
}