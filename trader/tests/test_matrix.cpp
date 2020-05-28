#include "matrix.h"
#include "gtest/gtest.h"


class MatrixTest : public ::testing::Test {
protected:
  void SetUp(void) override {
    matA.Resize(3, 3);
    matB.Resize(3, 3);

    matA.Clear(2.0);
    matB.Clear(4.0);
  }

  void TearDown(void) override {
  }

public:
  dMatrix matA;
  dMatrix matB;

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
  dMatrix mat1;
  EXPECT_EQ(mat1.Rows(), 0);
  EXPECT_EQ(mat1.Cols(), 0);
  mat1.Resize(3, 3);
  EXPECT_EQ(mat1.Rows(), 3);
  EXPECT_EQ(mat1.Cols(), 3);
  EXPECT_DOUBLE_EQ(mat1(1, 2), 0.0);
  EXPECT_DOUBLE_EQ(mat1(5, 2), 0.0);
  mat1.Clear(1.0);
  EXPECT_DOUBLE_EQ(mat1(1, 2), 1.0);
  EXPECT_DOUBLE_EQ(mat1(5, 2), 0.0);
}

TEST_F(MatrixTest, MatrixAddition) {
  dMatrix matAdd(matA + matB);
  EXPECT_DOUBLE_EQ(matAdd(2, 2), 6.0);

  matA += matB;
  EXPECT_DOUBLE_EQ(matA(2, 2), 6.0);
}

TEST_F(MatrixTest, ScalarAddition) {
  dMatrix scaAdd(matA + 2.0);
  EXPECT_DOUBLE_EQ(scaAdd(2, 2), 4.0);

  matA += 2.0;
  EXPECT_DOUBLE_EQ(matA(2, 2), 8.0);
}

TEST_F(MatrixTest, MatrixSubtraction) {
  dMatrix mat(matA - matB);
  EXPECT_DOUBLE_EQ(mat(2, 2), -2.0);

  matA -= matB;
  EXPECT_DOUBLE_EQ(matA(2, 2), -2.0);
}

TEST_F(MatrixTest, ScalarSubtraction) {
  dMatrix mat(matA - 2.0);
  EXPECT_DOUBLE_EQ(mat(2, 2), 0.0);

  matA -= matB;
  EXPECT_DOUBLE_EQ(matA(2, 2), -2.0);

  matA -= 2.0;
  EXPECT_DOUBLE_EQ(matA(2, 2), -4.0);
}

TEST_F(MatrixTest, MatrixMultiplication) {
  EXPECT_TRUE(false);
}

TEST_F(MatrixTest, ScalarMultiplication) {
  dMatrix mat(matA * 2);
  EXPECT_DOUBLE_EQ(mat(2, 2), 4.0);

  matA *= 2;
  EXPECT_DOUBLE_EQ(matA(2, 2), 4.0);
}

TEST_F(MatrixTest, MatrixDivision) {
  EXPECT_TRUE(false);
}


TEST_F(MatrixTest, ScalarDivision) {
  dMatrix matMult(matA / 2);
  EXPECT_DOUBLE_EQ(matMult(2, 2), 1.0);

  matA /= 2;
  EXPECT_DOUBLE_EQ(matA(2, 2), 1.0);
}