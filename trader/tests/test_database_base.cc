#include "database_base.h"

#include <gtest/gtest.h>

class MockDatabase : public DatabaseBase {
public:
  bool connect(void) { return false; }
  void disconnect(void) {}

  LayerConfiguration* getLayer(std::string ticker, unsigned int layerNum) override { LayerConfiguration* x; return x; }
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
  EXPECT_FLOAT_EQ(5.5f, mDB->toFloat("5.5"));
}
