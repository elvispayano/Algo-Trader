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

#include "utilities/random_number.h"
#include <gmock/gmock.h>

MATCHER_P( EqMatrix, other, "Matrix Equality Matcher" ) {
  matrix in   = static_cast<matrix>( arg );
  matrix comp = static_cast<matrix>( other );
  if ( ( comp.rows() != in.rows() ) || ( comp.cols() != in.cols() ) )
    return false;

  bool equal = true;
  for ( unsigned int r = 0; r < comp.rows(); ++r ) {
    for ( unsigned int c = 0; c < comp.cols(); ++c ) {
      equal &= ( comp( r, c ) - in( r, c ) ) < 1E-8;
    }
  }
  return equal;
}

class MatrixResizeTest : public ::testing::Test {
protected:
  void SetUp( void ) override {
    rng = new RandomNumber();
    r   = rng->random();
    c   = rng->random();
  }

  void TearDown( void ) override {
    if ( rng ) {
      delete rng;
    }
  }

public:
  RandomNumber* rng;

  matrix mat;

  unsigned int r;
  unsigned int c;
};

TEST_F( MatrixResizeTest, NoValue ) {
  // Action
  mat.resize( r, c );

  // Evaluation
  EXPECT_EQ( r, mat.rows() );
  EXPECT_EQ( c, mat.cols() );
  EXPECT_DOUBLE_EQ( 0.0, mat( floor( r / 2 ), floor( c / 2 ) ) );
  EXPECT_DOUBLE_EQ( 0.0, mat( r * 2, c / 2 ) );
}

TEST_F( MatrixResizeTest, InitValue ) {
  double val = rng->random( -100, 100 );

  // Action
  mat.resize( r, c, val );

  // Evaluation
  EXPECT_EQ( r, mat.rows() );
  EXPECT_EQ( c, mat.cols() );
  EXPECT_DOUBLE_EQ( val, mat( floor( r / 2 ), floor( c / 2 ) ) );
  EXPECT_DOUBLE_EQ( 0.0, mat( r * 2, c / 2 ) );
}

TEST_F( MatrixResizeTest, InitVector ) {
  std::vector<double> val;
  for ( unsigned int i = 0; i < ( r * c ); ++i ) {
    val.push_back( rng->random( -100, 100 ) );
  }

  // Action
  mat.resize( r, c, val );

  // Evaluation
  EXPECT_EQ( r, mat.rows() );
  EXPECT_EQ( c, mat.cols() );
  EXPECT_DOUBLE_EQ( val[floor( r / 2 ) + r * floor( c / 2 )],
                    mat( floor( r / 2 ), floor( c / 2 ) ) );
  EXPECT_DOUBLE_EQ( 0.0, mat( r * 2, c / 2 ) );
}

class MatrixValueTest : public ::testing::Test {
protected:
  void SetUp( void ) override {
    rng            = new RandomNumber();
    unsigned int r = rng->random();
    unsigned int c = rng->random();
    mat.resize( r, c );
    ASSERT_TRUE( mat.rows() > 0 ) << "Non-Zero amount of rows required";
    ASSERT_TRUE( mat.cols() > 0 ) << "Non-Zero amount of columns required";
  }

  void TearDown( void ) override {
    if ( rng ) {
      delete rng;
    }
  }

public:
  RandomNumber* rng;

  matrix mat;
};

TEST_F( MatrixValueTest, Reset ) {
  // Setup
  mat.randomize();
  double randomValue = rng->random();

  // Action
  mat.reset( randomValue );

  // Evaluation
  for ( unsigned int r = 0; r < mat.rows(); ++r ) {
    for ( unsigned int c = 0; r < mat.cols(); ++c ) {
      EXPECT_DOUBLE_EQ( randomValue, mat( r, c ) );
    }
  }
}

TEST_F( MatrixValueTest, Clear ) {
  // Action
  mat.randomize();
  mat.clear();

  // Evaluation
  for ( unsigned int r = 0; r < mat.rows(); ++r ) {
    for ( unsigned int c = 0; r < mat.cols(); ++c ) {
      EXPECT_DOUBLE_EQ( 0.0, mat( r, c ) );
    }
  }
}

TEST_F( MatrixValueTest, Randomize ) {
  // Setup
  unsigned int r = mat.rows();
  unsigned int c = mat.cols();

  double       prevValue = mat( floor( r / 2 ), floor( c / 2 ) );
  unsigned int limit     = rng->random( 3, 10 );
  for ( unsigned int iter = 0; iter < limit; ++iter ) {
    mat.randomize();
    double matrixValue = mat( floor( r / 2 ), floor( c / 2 ) );
    EXPECT_NE( prevValue, matrixValue );
    prevValue = matrixValue;
  }
}

TEST_F( MatrixValueTest, Transpose ) {
  mat.randomize();
  matrix temp = mat.transpose();

  EXPECT_EQ( mat.rows(), temp.cols() );
  EXPECT_EQ( mat.cols(), temp.rows() );
  for ( unsigned int r = 0; r < mat.rows(); ++r ) {
    for ( unsigned int c = 0; c < mat.cols(); ++c ) {
      EXPECT_EQ( mat( r, c ), temp( c, r ) );
    }
  }
}

class MatrixAdditionTest : public ::testing::Test {
protected:
  void SetUp( void ) override {
    rng            = new RandomNumber();
    unsigned int r = rng->random();
    unsigned int c = rng->random();

    A.resize( r, c );
    B.resize( r, c );
    C.resize( r, c );
    A.randomize();
    B.randomize();
    C.randomize();
  }

  void TearDown( void ) override {
    if ( rng ) {
      delete rng;
    }
  }

public:
  RandomNumber* rng;

  matrix A;
  matrix B;
  matrix C;
};

TEST_F( MatrixAdditionTest, Commutative ) {
  EXPECT_THAT( A + B, EqMatrix( B + A ) );
}

TEST_F( MatrixAdditionTest, Associative ) {
  EXPECT_THAT( A + ( B + C ), EqMatrix( ( A + B ) + C ) );
}

TEST_F( MatrixAdditionTest, Identity ) {
  B.clear();
  EXPECT_THAT( A + B, EqMatrix( A ) );
}

TEST_F( MatrixAdditionTest, Inverse ) {
  B.clear();
  EXPECT_THAT( B, EqMatrix( A - A ) );
}

class MatrixScalarMultiplicationTest : public ::testing::Test {
protected:
  void SetUp( void ) override {
    rng            = new RandomNumber();
    unsigned int r = rng->random();
    unsigned int c = rng->random();

    k = rng->random( -100, 100 );
    c = rng->random( -100, 100 );

    A.resize( r, c );
    B.resize( r, c );
    A.randomize();
    B.randomize();
  }

  void TearDown( void ) override {
    if ( rng ) {
      delete rng;
    }
  }

public:
  RandomNumber* rng;

  matrix A;
  matrix B;

  double k;
  double c;
};

TEST_F( MatrixScalarMultiplicationTest, Distributive ) {
  EXPECT_THAT( ( A + B ) * k, EqMatrix( A * k + B * k ) );
}

TEST_F( MatrixScalarMultiplicationTest, Commulative ) {
  EXPECT_THAT( A * ( k + c ), EqMatrix( A * k + A * c ) );
}

TEST_F( MatrixScalarMultiplicationTest, Associative ) {
  EXPECT_THAT( A * ( k * c ), EqMatrix( ( A * k ) * c ) );
}

TEST_F( MatrixScalarMultiplicationTest, Identity ) {
  EXPECT_THAT( A, EqMatrix( A * 1 ) );
}
