/*
  Title:
    Matrix Unit Test

  Description:
    This unit test will ensure all functionality of the created
    matrix library is implemented as expected. Tests will be
    separated by Function/Operator being tested.

  Author:
    Elvis Payano
*/

// Utility Includes
#include "utilities/matrix.h"

// Google Test Includes
#include "gtest/gtest.h"

// Unit test framework setup
class MatrixTest : public ::testing::Test {
protected:
  void SetUp( void ) override {
    matA.resize( 2, 2, 2.0 );
    matB.resize( 2, 2, 4.0 );
  }

public:
  dMatrix matA;
  dMatrix matB;
};

/*
  Test:         Constructor Default
  Description:
    Create a default matrix object
*/
TEST_F( MatrixTest, ConstructorDefault ) {
  dMatrix mat;
  EXPECT_EQ( 1, mat.rows() );
  EXPECT_EQ( 1, mat.cols() );
}

/*
  Test:         Constructor Size
  Description:
    Create a matrix object with a defined size, but
    no defined initial value
*/
TEST_F( MatrixTest, ConstructorSize ) {
  dMatrix mat( 2, 4, 0.0 );
  EXPECT_EQ( 2, mat.rows() );
  EXPECT_EQ( 4, mat.cols() );
}

/*
  Test:         Constructor Value
  Description:
    Create a matrix object with a defined size and a
    define initial value
*/
TEST_F( MatrixTest, ConstructorValue ) {
  dMatrix mat( 4, 2, 2.0 );
  EXPECT_EQ( 4, mat.rows() );
  EXPECT_EQ( 2, mat.cols() );
  EXPECT_DOUBLE_EQ( 2.0, mat( 0, 0 ) );
}

/*
  Test:         Clear Default
  Description:
    Clear all elements of a matrix to a default of zero
*/
TEST_F( MatrixTest, ClearDefault ) {
  dMatrix mat( 2, 2, 2.0 );
  EXPECT_DOUBLE_EQ( 2.0, mat( 0, 0 ) );

  mat.clear( 0.0 );
  EXPECT_DOUBLE_EQ( 0.0, mat( 0, 0 ) );
}

/*
  Test:         Clear Value
  Description:
    Clear all elements and reset all values to the provided
    input
*/
TEST_F( MatrixTest, ClearValue ) {
  dMatrix mat( 2, 2, 2.0 );
  EXPECT_DOUBLE_EQ( 2.0, mat( 0, 0 ) );

  mat.clear( 4.0 );
  EXPECT_DOUBLE_EQ( 4.0, mat( 0, 0 ) );
}

/*
  Test:         Resize Default
  Description:
    Resize a matrix and default all values to zero
*/
TEST_F( MatrixTest, ResizeDefault ) {
  dMatrix mat( 2, 2, 2.0 );
  EXPECT_EQ( 2, mat.rows() );
  EXPECT_EQ( 2, mat.cols() );

  mat.resize( 4, 3, 0.0 );
  EXPECT_EQ( 4, mat.rows() );
  EXPECT_EQ( 3, mat.cols() );
  EXPECT_DOUBLE_EQ( 0.0, mat( 0, 0 ) );
}

/*
  Test:         Resize Value
  Description:
    Clear all elements of a matrix and reset to a provided
    value
*/
TEST_F( MatrixTest, ResizeValue ) {
  dMatrix mat( 2, 2, 2.0 );
  EXPECT_EQ( 2, mat.rows() );
  EXPECT_EQ( 2, mat.cols() );

  mat.resize( 4, 3, 3.0 );
  EXPECT_EQ( 4, mat.rows() );
  EXPECT_EQ( 3, mat.cols() );
  EXPECT_DOUBLE_EQ( 3.0, mat( 0, 0 ) );
}

/*
  Test:         For Each
  Description:
    Each element in matrix is modified by inserted function
*/
double add2( double x ) {
  return x + 2;
}
TEST_F( MatrixTest, ForEach ) {
  dMatrix mat( 2, 2, 2.0 );
  mat.forEach( add2 );
  EXPECT_DOUBLE_EQ( 4.0, mat( 0, 0 ) );
}

/*
  Test:         Matrix Addition
  Description:
    Perform addition of 2 matrices
*/
TEST_F( MatrixTest, MatrixAddition ) {
  dMatrix matAdd( matA + matB );
  EXPECT_DOUBLE_EQ( matAdd( 0, 0 ), 6.0 );
}

/*
  Test:         Matrix Addition Assignment
  Description:
    Perform addition assignment with a matrix
*/
TEST_F( MatrixTest, MatrixAdditionAssignment ) {
  matA += matB;
  EXPECT_DOUBLE_EQ( matA( 0, 0 ), 6.0 );
}

/*
  Test:         Scalar Addition
  Description:
    Perform scalar addition of a matrix and a scalar
*/
TEST_F( MatrixTest, ScalarAddition ) {
  dMatrix scaAdd( matA + 2.0 );
  EXPECT_DOUBLE_EQ( scaAdd( 0, 0 ), 4.0 );
}

/*
  Test:         Scalar Addition Assignment
  Description:
    Perform scalar addition assignment with a scalar value
*/
TEST_F( MatrixTest, ScalarAdditionAssignment ) {
  matA += 2.0;
  EXPECT_DOUBLE_EQ( matA( 0, 0 ), 4.0 );
}

/*
  Test:         Matrix Subtraction
  Description:
    Perform subtraction of 2 matrices
*/
TEST_F( MatrixTest, MatrixSubtraction ) {
  dMatrix mat( matA - matB );
  EXPECT_DOUBLE_EQ( mat( 0, 0 ), -2.0 );
}

/*
  Test:         Matrix Subtraction Assignment
  Description:
    Perform subtraction assignment with a matrix
*/
TEST_F( MatrixTest, MatrixSubtractionAssignment ) {
  matA -= matB;
  EXPECT_DOUBLE_EQ( matA( 0, 0 ), -2.0 );
}

/*
  Test:         Scalar Subtraction
  Description:
    Perform subtraction of 2 matrices
*/
TEST_F( MatrixTest, ScalarSubtraction ) {
  dMatrix mat( matA - 4.0 );
  EXPECT_DOUBLE_EQ( mat( 0, 0 ), -2.0 );
}

/*
  Test:         Scalar Subtraction Assignment
  Description:
    Perform subtraction assignment with a matrix
*/
TEST_F( MatrixTest, ScalarSubtractionAssignment ) {
  matA -= 4.0;
  EXPECT_DOUBLE_EQ( matA( 0, 0 ), -2.0 );
}

/*
  Test:         Matrix Multiplication
  Description:
    Perform multiplication of 2 matrices
*/
TEST_F( MatrixTest, MatrixMultiplication ) {
  dMatrix mat1( 3, 2, 2.0 );
  dMatrix mat2( 2, 3, 4.0 );
  dMatrix mat( mat1 * mat2 );

  EXPECT_EQ( mat.rows(), 3 );
  EXPECT_EQ( mat.cols(), 3 );
  EXPECT_DOUBLE_EQ( mat( 0, 0 ), 16 );
}

/*
  Test:         Matrix Multiplication Assignment
  Description:
    Perform multiplication assignment with matrix
*/
TEST_F( MatrixTest, MatrixMultiplicationAssignment ) {
  dMatrix mat1( 3, 2, 2.0 );
  dMatrix mat2( 2, 3, 4.0 );
  mat1 *= mat2;

  EXPECT_EQ( mat1.rows(), 3 );
  EXPECT_EQ( mat1.cols(), 3 );
  EXPECT_DOUBLE_EQ( mat1( 0, 0 ), 16 );
}

/*
  Test:         Scalar Multiplication
  Description:
    Perform multiplication with a scalar
*/
TEST_F( MatrixTest, ScalarMultiplication ) {
  dMatrix mat( matA * 2 );
  EXPECT_DOUBLE_EQ( mat( 0, 0 ), 4.0 );
}

/*
  Test:         Scalar Multiplication Assignment
  Description:
    Perform multiplication assignment with a scalar
*/
TEST_F( MatrixTest, ScalarMultiplicationAssignment ) {
  matA *= 2;
  EXPECT_DOUBLE_EQ( matA( 0, 0 ), 4.0 );
}

/*
  Test:         Scalar Division
  Description:
    Perform division with a scalar
*/
TEST_F( MatrixTest, ScalarDivision ) {
  dMatrix mat( matA / 2 );
  EXPECT_DOUBLE_EQ( mat( 0, 0 ), 1.0 );
}

/*
  Test:         Scalar Division Assignment
  Description:
    Perform division assignment with a scalar
*/
TEST_F( MatrixTest, ScalarDivisionAssignment ) {
  matA /= 2;
  EXPECT_DOUBLE_EQ( matA( 0, 0 ), 1.0 );
}
