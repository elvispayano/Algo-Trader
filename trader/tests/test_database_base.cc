#include "database_base.h"

#include <gtest/gtest.h>

class MockDatabase : public DatabaseBase {
public:
  bool connect(void) { return false; }
  void disconnect(void) {}
  int getNetworkCount(void) { return 0; }
  std::string getNetwork(size_t id) { return NULL; }
  int getLayerCount(std::string ticker) { return 0; }

  int getInputs(std::string ticker, int layerNum) { return 0; }
  int getNodes(std::string ticker, int layerNum) {return 0;}
  int getIndex(std::string ticker, int layerNum) {return 0;}
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

TEST_F(DatabaseTest, IntConversion) {
  EXPECT_EQ(5, mDB->toInt("5"));
}

TEST_F(DatabaseTest, FloatConversion) {
  EXPECT_FLOAT_EQ(5.5f, mDB->toInt("5.5"));
}
