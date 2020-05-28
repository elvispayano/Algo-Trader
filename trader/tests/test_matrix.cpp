#include "matrix.h"
#include "gtest/gtest.h"

namespace {
  class MatrixTest : public ::testing::Test {
  public:
    dMatrix mat;
  };

  TEST_F(MatrixTest, Initialize) {
    dMatrix mat1;
    EXPECT_EQ(mat1.Rows(), 0);
    EXPECT_EQ(mat1.Cols(), 0);
    EXPECT_DOUBLE_EQ(mat1(1, 2), 0.0);
    EXPECT_DOUBLE_EQ(mat1(5, 2), 0.0);
    
    
    dMatrix mat2(3, 3, 1.0);
    EXPECT_EQ(mat2.Rows(), 3);
    EXPECT_EQ(mat2.Cols(), 3);
    EXPECT_DOUBLE_EQ(mat2(1, 2), 1.0);
    EXPECT_DOUBLE_EQ(mat2(5, 2), 0.0);
  }

  TEST_F(MatrixTest, Reshaping) {
    EXPECT_EQ(mat.Rows(), 0);
    EXPECT_EQ(mat.Cols(), 0);
    mat.Resize(3, 3);
    EXPECT_EQ(mat.Rows(), 3);
    EXPECT_EQ(mat.Cols(), 3);
    EXPECT_DOUBLE_EQ(mat(1, 2), 0.0);
    EXPECT_DOUBLE_EQ(mat(5, 2), 0.0);
    mat.Clear(1.0);
    EXPECT_DOUBLE_EQ(mat(1, 2), 1.0);
    EXPECT_DOUBLE_EQ(mat(5, 2), 0.0);
  }
}