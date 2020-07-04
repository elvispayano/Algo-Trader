/*
  Title:
    Database Base Unit Test

  Description:
    This unit test will test the standard functionality provided to all
    derived database types

  Author:
    Elvis Payano
*/

// Interface Includes
#include "database_base.h"

// Google Test Includes
#include <gtest/gtest.h>

// Creating concrete class to test abstract database base class
class MockDatabase : public DatabaseBase {
public:
  bool connect(void) { return false; }
  void disconnect(void) {}

  LayerConfiguration getLayer(std::string ticker, unsigned int layerNum) override { return temp; }
  int getNetworkCount(void) override { return 1; }
  std::string getNetwork(size_t id) override { return "XYZ"; }
  int getLayerCount(std::string ticker) override { return 1; }

private:
  LayerConfiguration temp;
};

class DatabaseTest : public ::testing::Test {
protected:
  void SetUp(void) override {
    mDB = new MockDatabase();
  }

  void TearDown(void) override {
    if (mDB)
      delete mDB;
  }

public:
  MockDatabase* mDB;
};

/*
  Test:         IntConversion
  Description:
    Ensure input string can be converted into an integer
*/
TEST_F(DatabaseTest, IntConversion) {
  EXPECT_EQ(5, mDB->toInt("5"));
}

/*
  Test:         FloatConversion
  Description:
    Ensure input string can be converted into a float
*/
TEST_F(DatabaseTest, FloatConversion) {
  EXPECT_FLOAT_EQ(5.5f, mDB->toFloat("5.5"));
}
