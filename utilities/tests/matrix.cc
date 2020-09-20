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
#include "utilities/random_number.h"

// Google Test Includes
#include "gtest/gtest.h"
#include <gmock/gmock.h>

MATCHER_P( EqMatrix, other, "Matrix Equality Matcher" ) {
  Matrix in   = static_cast<Matrix>( arg );
  Matrix comp = static_cast<Matrix>( other );
  if ( ( comp.rows() != in.rows() ) || ( comp.cols() != in.cols() ) )
    return false;

  bool equal = true;
  for ( unsigned int r = 0; r < comp.rows(); ++r ) {
    for ( unsigned int c = 0; c < comp.cols(); ++c ) {
      equal &= abs( comp( r, c ) - in( r, c ) ) < 1E-8;
    }
  }
  return equal;
}

MATCHER_P( NeqMatrix, other, "Matrix Inequality Matcher" ) {
  Matrix in   = static_cast<Matrix>( arg );
  Matrix comp = static_cast<Matrix>( other );
  if ( ( comp.rows() != in.rows() ) || ( comp.cols() != in.cols() ) )
    return true;

  bool equal = false;
  for ( unsigned int r = 0; r < comp.rows(); ++r ) {
    for ( unsigned int c = 0; c < comp.cols(); ++c ) {
      equal |= abs( comp( r, c ) - in( r, c ) ) > 1E-8;
    }
  }
  return equal;
}

class MatrixSizeTest : public ::testing::Test {
protected:
  void SetUp( void ) override {
    rng = new RandomNumber();
    mr  = rng->random();
    mc  = rng->random();
  }

  void TearDown( void ) override {
    if ( rng ) {
      delete rng;
    }
  }

public:
  RandomNumber* rng;

  unsigned int mr;
  unsigned int mc;
};

TEST_F( MatrixSizeTest, Empty ) {
  Matrix mat( mr, mc );

  EXPECT_EQ( mr, mat.rows() );
  EXPECT_EQ( mc, mat.cols() );

  for ( unsigned int r = 0; r < mr; ++r ) {
    for ( unsigned int c = 0; c < mc; ++c ) {
      EXPECT_DOUBLE_EQ( 0.0, mat( r, c ) );
    }
  }
}

TEST_F( MatrixSizeTest, Value ) {
  double randomValue = rng->random();
  Matrix mat( mr, mc, randomValue );

  EXPECT_EQ( mr, mat.rows() );
  EXPECT_EQ( mc, mat.cols() );

  for ( unsigned int r = 0; r < mr; ++r ) {
    for ( unsigned int c = 0; c < mc; ++c ) {
      EXPECT_DOUBLE_EQ( randomValue, mat( r, c ) );
    }
  }
}

TEST_F( MatrixSizeTest, Vector ) {
  std::vector<double> vec;
  for ( unsigned int iter = 0; iter < ( mr * mc ); ++iter ) {
    vec.push_back( rng->random() );
  }
  Matrix mat( mr, mc, vec );

  EXPECT_EQ( mr, mat.rows() );
  EXPECT_EQ( mc, mat.cols() );

  unsigned int element = 0;
  for ( unsigned int c = 0; c < mc; ++c ) {
    for ( unsigned int r = 0; r < mr; ++r ) {
      EXPECT_DOUBLE_EQ( vec[element++], mat( r, c ) );
    }
  }
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

  Matrix mat;

  unsigned int r;
  unsigned int c;
};

TEST_F( MatrixResizeTest, NoValue ) {
  // Action
  mat.resize( r, c );

  // Evaluation
  EXPECT_EQ( r, mat.rows() );
  EXPECT_EQ( c, mat.cols() );

  unsigned int rEval = rng->random( 0, r - 1 );
  unsigned int cEval = rng->random( 0, c - 1 );
  EXPECT_DOUBLE_EQ( 0.0, mat( rEval, cEval ) );
}

TEST_F( MatrixResizeTest, InitValue ) {
  double val = rng->random( -100, 100 );

  // Action
  mat.resize( r, c, val );

  // Evaluation
  EXPECT_EQ( r, mat.rows() );
  EXPECT_EQ( c, mat.cols() );

  unsigned int rEval = rng->random( 0, r - 1 );
  unsigned int cEval = rng->random( 0, c - 1 );
  EXPECT_DOUBLE_EQ( val, mat( rEval, cEval ) );
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

  unsigned int rEval = rng->random( 0, r - 1 );
  unsigned int cEval = rng->random( 0, c - 1 );
  EXPECT_DOUBLE_EQ( val[rEval + r * cEval], mat( rEval, cEval ) );
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

  Matrix mat;
};

TEST_F( MatrixValueTest, Reset ) {
  // Setup
  mat.randomize();
  double randomValue = rng->random();

  // Action
  mat.reset( randomValue );

  // Evaluation
  for ( unsigned int r = 0; r < mat.rows(); ++r ) {
    for ( unsigned int c = 0; c < mat.cols(); ++c ) {
      EXPECT_DOUBLE_EQ( randomValue, mat( r, c ) );
    }
  }
}

TEST_F( MatrixValueTest, Clear ) {
  // Action
  mat.randomize();
  mat.clear();

  // Evaluation
  EXPECT_EQ( 0, mat.rows() );
  EXPECT_EQ( 0, mat.cols() );
}

TEST_F( MatrixValueTest, Randomize ) {
  // Setup
  unsigned int r = mat.rows();
  unsigned int c = mat.cols();

  unsigned int rEval     = rng->random( 0, r - 1 );
  unsigned int cEval     = rng->random( 0, c - 1 );
  double       prevValue = mat( rEval , cEval );
  unsigned int limit     = rng->random( 3, 10 );
  for ( unsigned int iter = 0; iter < limit; ++iter ) {
    mat.randomize();
    double matrixValue = mat( rEval, cEval );
    EXPECT_NE( prevValue, matrixValue );
    prevValue = matrixValue;
  }
}

TEST_F( MatrixValueTest, Transpose ) {
  mat.randomize();
  Matrix temp = mat.transpose();

  EXPECT_EQ( mat.rows(), temp.cols() );
  EXPECT_EQ( mat.cols(), temp.rows() );
  for ( unsigned int r = 0; r < mat.rows(); ++r ) {
    for ( unsigned int c = 0; c < mat.cols(); ++c ) {
      EXPECT_EQ( mat( r, c ), temp( c, r ) );
    }
  }
}

class MatrixArithmeticTest : public ::testing::Test {
protected:
  void SetUp( void ) override {
    rng            = new RandomNumber();
    unsigned int r = rng->random();
    unsigned int c = rng->random();

    A.resize( r, c );
    A.randomize();
    ASSERT_TRUE( A.rows() > 0 ) << "A: Non-Zero amount of rows required";
    ASSERT_TRUE( A.cols() > 0 ) << "A: Non-Zero amount of columns required";

    B.resize( r, c );
    B.randomize();
    ASSERT_TRUE( B.rows() > 0 ) << "B: Non-Zero amount of rows required";
    ASSERT_TRUE( B.cols() > 0 ) << "B: Non-Zero amount of columns required";

    C.resize( r, c );
    C.randomize();
    ASSERT_TRUE( C.rows() > 0 ) << "C: Non-Zero amount of rows required";
    ASSERT_TRUE( C.cols() > 0 ) << "C: Non-Zero amount of columns required";

    D.resize( c, r );
    D.randomize();
    ASSERT_TRUE( D.rows() > 0 ) << "D: Non-Zero amount of rows required";
    ASSERT_TRUE( D.cols() > 0 ) << "D: Non-Zero amount of columns required";
  }

  void TearDown( void ) override {
    if ( rng ) {
      delete rng;
    }
  }

public:
  RandomNumber* rng;

  Matrix A;
  Matrix B;
  Matrix C;
  Matrix D;
};

// Matrix Addition
TEST_F( MatrixArithmeticTest, AdditionCommutative ) {
  EXPECT_THAT( A + B, EqMatrix( B + A ) );
}

TEST_F( MatrixArithmeticTest, AdditionAssociative ) {
  EXPECT_THAT( A + ( B + C ), EqMatrix( ( A + B ) + C ) );
}

TEST_F( MatrixArithmeticTest, AdditionIdentity ) {
  B.reset( 0.0 );
  EXPECT_THAT( A + B, EqMatrix( A ) );
}

TEST_F( MatrixArithmeticTest, AdditionSizing ) {
  EXPECT_EQ( A.rows(), ( A + B ).rows() );
  EXPECT_EQ( A.cols(), ( A + B ).cols() );
}

// Matrix Subtraction
TEST_F( MatrixArithmeticTest, SubtractionAnticommutative ) {
  EXPECT_THAT( A - B, EqMatrix( ( B - A ) * -1 ) );
}

TEST_F( MatrixArithmeticTest, SubtractionNonAssociative ) {
  EXPECT_THAT( ( A - B ) - C, NeqMatrix( A - ( B - C ) ) );
}

TEST_F( MatrixArithmeticTest, SubtractionSizing ) {
  EXPECT_EQ( A.rows(), ( A - B ).rows() );
  EXPECT_EQ( A.cols(), ( A - B ).cols() );
}

// TODO: Matrix Multiplication
TEST_F( MatrixArithmeticTest, MultiplicationSizing ) {
  EXPECT_EQ( A.rows(), ( A * D ).rows() );
  EXPECT_EQ( D.cols(), ( A * D ).cols() );
}

// TODO: Matrix Division

class MatrixScalarArithmeticTest : public ::testing::Test {
protected:
  void SetUp( void ) override {
    rng            = new RandomNumber();
    unsigned int r = rng->random();
    unsigned int c = rng->random();

    j = rng->random( -100, 100 );
    k = rng->random( -100, 100 );

    A.resize( r, c );
    A.randomize();
    ASSERT_TRUE( A.rows() > 0 ) << "A: Non-Zero amount of rows required";
    ASSERT_TRUE( A.cols() > 0 ) << "A: Non-Zero amount of columns required";

    B.resize( r, c );
    B.randomize();
    ASSERT_TRUE( B.rows() > 0 ) << "B: Non-Zero amount of rows required";
    ASSERT_TRUE( B.cols() > 0 ) << "B: Non-Zero amount of columns required";
  }

  void TearDown( void ) override {
    if ( rng ) {
      delete rng;
    }
  }

public:
  RandomNumber* rng;

  Matrix A;
  Matrix B;

  double j;
  double k;
};

// Scalar Addition
TEST_F( MatrixScalarArithmeticTest, AdditionAssociative ) {
  EXPECT_THAT( ( k + A ) + j, EqMatrix( k + ( A + j ) ) );
}

TEST_F( MatrixScalarArithmeticTest, AdditionCommutative ) {
  EXPECT_THAT( A + k, EqMatrix( k + A ) );
}

TEST_F( MatrixScalarArithmeticTest, AdditionIdentity ) {
  EXPECT_THAT( A + 0, EqMatrix( A ) );
}

TEST_F( MatrixScalarArithmeticTest, AdditionSizing ) {
  EXPECT_EQ( A.rows(), ( A + k ).rows() );
  EXPECT_EQ( A.cols(), ( A + k ).cols() );
}

// Scalar Subtraction
TEST_F( MatrixScalarArithmeticTest, SubtractionAnticommutative ) {
  EXPECT_THAT( A - k, EqMatrix( -1 * ( k - A ) ) );
}

TEST_F( MatrixScalarArithmeticTest, SubtractionNonAssociative ) {
  EXPECT_THAT( ( j - A ) - k, NeqMatrix( j - ( A - k ) ) );
}

TEST_F( MatrixScalarArithmeticTest, SubtractionSizing ) {
  EXPECT_EQ( A.rows(), ( A - k ).rows() );
  EXPECT_EQ( A.cols(), ( A - k ).cols() );
}

// Scalar Multiplication
TEST_F( MatrixScalarArithmeticTest, MultiplicationDistributive ) {
  EXPECT_THAT( ( A + B ) * k, EqMatrix( A * k + B * k ) );
}

TEST_F( MatrixScalarArithmeticTest, MultiplicationCommulative ) {
  EXPECT_THAT( A * ( k + j ), EqMatrix( A * k + A * j ) );
}

TEST_F( MatrixScalarArithmeticTest, MultiplicationAssociative ) {
  EXPECT_THAT( k * ( A * j ), EqMatrix( ( k * A ) * j ) );
}

TEST_F( MatrixScalarArithmeticTest, MultiplicationIdentity ) {
  EXPECT_THAT( A, EqMatrix( A * 1 ) );
}

TEST_F( MatrixScalarArithmeticTest, MultiplicationSizing ) {
  EXPECT_EQ( A.rows(), ( A * k ).rows() );
  EXPECT_EQ( A.cols(), ( A * k ).cols() );
}

// Scalar Division
TEST_F( MatrixScalarArithmeticTest, DivisionInverse ) {
  A.reset( k );
  B.reset( 1.0 );
  EXPECT_THAT( B, EqMatrix( A / k ) );
}

TEST_F( MatrixScalarArithmeticTest, DivisionIdentity ) {
  EXPECT_THAT( A, EqMatrix( A / 1 ) );
}

TEST_F( MatrixScalarArithmeticTest, DivisionSizing ) {
  EXPECT_EQ( A.rows(), ( A / k ).rows() );
  EXPECT_EQ( A.cols(), ( A / k ).cols() );
}

// TODO: Assignment Matrix +
// TODO: Assignment Matrix -
// TODO: Assignment Matrix *
// TODO: Assignment Matrix /

// TODO: Assignment Scalar +
// TODO: Assignment Scalar -
// TODO: Assignment Scalar *
// TODO: Assignment Scalar /

class MatrixSetTest : public ::testing::Test {
protected:
  void SetUp( void ) override {
    rng            = new RandomNumber();
    unsigned int r = rng->random();
    unsigned int c = rng->random();

    A.resize( r, c );
    A.randomize();
    ASSERT_TRUE( A.rows() > 0 ) << "A: Non-Zero amount of rows required";
    ASSERT_TRUE( A.cols() > 0 ) << "A: Non-Zero amount of columns required";

    B.resize( r, c );
    B.randomize();
    ASSERT_TRUE( B.rows() > 0 ) << "B: Non-Zero amount of rows required";
    ASSERT_TRUE( B.cols() > 0 ) << "B: Non-Zero amount of columns required";
  }

  void TearDown( void ) override {
    if ( rng ) {
      delete rng;
    }
  }

public:
  RandomNumber* rng;

  Matrix A;
  Matrix B;
};

// TODO: Set Matrix
// TODO: Set/Get Row (Matrix)
// TODO: Set/Get Row (Vector)
// TODO: Set/Get Col (Matrix)
// TODO: Set/Get Col (Vector)

// TODO: SubMatrix

// TODO: ForEach
