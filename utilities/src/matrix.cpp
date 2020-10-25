/// Matrix
///
/// Functionality for processing matrix data
///
/// \author   Elvis Payano
/// \date     18/09/2020
/// \version  0.0.1

// Utility Includes
#include "utilities/matrix.h"
#include "utilities/random_number.h"

// Standard Includes
#include <string>

/// @fn     Matrix( void )
/// @brief  Initialize an empty 0-by-0 matrix
Matrix::Matrix( void ) {
  mr = 0;
  mc = 0;
  clear();
}

/// @fn     Matrix( const Matrix& in )
/// @param  in Initialization matrix
/// @brief  Initialize a matrix by copying
Matrix::Matrix( const Matrix& in ) {
  mr = 0;
  mc = 0;
  resize( in.mr, in.mc );
  unsigned int totalElements = mr * mc;
  memcpy( mat, in.mat, sizeof( double ) * ( totalElements ) );
}

/// @fn     Matrix( unsigned int r, unsigned int c )
/// @param  r   Number of rows in matrix
/// @param  c   Number of columns in matrix
/// @brief  Initialize an empty r-by-c matrix
Matrix::Matrix( unsigned int r, unsigned int c ) {
  mr = 0;
  mc = 0;
  resize( r, c );
}

/// @fn     Matrix( unsigned int r, unsigned int c )
/// @param  r       Number of rows in matrix
/// @param  c       Number of columns in matrix
/// @param  initVal Initial value of all elements in matrix
/// @brief  Initialize an r-by-c matrix with all elments set to an initial value
Matrix::Matrix( unsigned int r, unsigned int c, double initVal ) {
  mr = 0;
  mc = 0;
  resize( r, c, initVal );
}

/// @fn     Matrix( unsigned int r, unsigned int c, double* initVec )
/// @param  r       Number of rows in matrix
/// @param  c       Number of columns in matrix
/// @param  initVec Vector containing all elements in matrix
/// @brief  Initialize an r-by-c matrix set with provided elements
Matrix::Matrix( unsigned int r, unsigned int c, double* initVec ) {
  mr = 0;
  mc = 0;
  resize( r, c, initVec );
}

/// @fn     ~Matrix( void )
/// @brief  Clear memory and reset values
Matrix::~Matrix( void ) {
  clear();
}

/// @fn     void reset( double initVal )
/// @param  initVal   Desired initial value
/// @brief  Reset matrix and set every element in matrix to value provided
void Matrix::reset( double initVal ) {
  if ( mr == 0 || mc == 0 ) {
    return;
  }

  for (unsigned int i = 0; i < mr * mc; ++i) {
    mat[i] = initVal;
  }
}

/// @fn     void clear( void )
/// @brief  Clear the matrix of any data stored
void Matrix::clear( void ) {
  if (mr * mc <= 0) {
    return;
  }
  mr = 0;
  mc = 0;
  free( mat );
}

/// @fn     void randomize( void )
/// @brief  Set all elements in matrix to random values
void Matrix::randomize( void ) {
  static RandomNumber rng;
  for ( unsigned int i = 0; i < mr * mc; ++i ) {
    mat[i] = rng.random( -100, 100 );
  }
}

/// @fn     void resize( unsigned int r, unsigned int c )
/// @param  r   Desired row count in resized matrix
/// @param  c   Desired column count in resized matrix
/// @brief  Resize the matrix to a new desired size. Removes all data currently
///         in matrix
void Matrix::resize( unsigned int r, unsigned int c ) {
  resize( r, c, 0.0 );
}

/// @fn     void resize( unsigned int r, unsigned int c, double initVal )
/// @param  r         Desired row count in resized matrix
/// @param  c         Desired column count in resized matrix
/// @param  initVal   Initial value to set matrix elements
/// @brief  Resize the matrix to a new desired size. Removes all data currently
///         in matrix
void Matrix::resize( unsigned int r, unsigned int c, double initVal ) {
  clear();
  unsigned int totalElements = r * c;

  mat = (double*)malloc( sizeof( double ) * totalElements );

  mr = r;
  mc = c;
  reset( initVal );
}

/// @fn     void resize( unsigned int r, unsigned int c, vector<double> initVal
/// )
/// @param  r         Desired row count in resized matrix
/// @param  c         Desired column count in resized matrix
/// @param  initArray Initial array of values to set matrix elements
/// @brief  Resize the matrix to a new desired size. Removes all data currently
///         in matrix
void Matrix::resize( unsigned int r, unsigned int c, double* initVec ) {
  clear();
  unsigned int totalElements = r * c;

  mat = (double*)malloc( sizeof( double ) * totalElements );

  mr = r;
  mc = c;

  for ( unsigned int iter = 0; iter < totalElements; ++iter ) {
    mat[iter] = initVec[iter];
  }
}

Matrix Matrix::subMatrix( unsigned int r, unsigned int c ) {
  return *this;
}

/// @fn     Matrix getRow( unsigned int r )
/// @param  r   Row index
/// @brief  Get a single row from within the matrix
Matrix Matrix::getRow( unsigned int r ) {
  Matrix row( 1, mc );
  for ( unsigned int c = 0; c < mc; ++c ) {
    row( 0, c ) = this->operator()( r, c );
  }
  return row;
}

/// @fn     Matrix getCol( unsigned int c )
/// @param  c   Column index
/// @brief  Get a single column from within the matrix
Matrix Matrix::getCol( unsigned int c ) {
  Matrix column( mr, 1 );
  for ( unsigned int r = 0; r < mr; ++r ) {
    column( r, 0 ) = this->operator()( r, c );
  }
  return column;
}

/// @fn     void setRow( unsigned int r, Matrix row )
/// @param  r     Row index
/// @param  row   Row matrix
/// @brief  Set the row of the matrix with the provided data
void Matrix::setRow( unsigned int r, Matrix row ) {
  if ( row.cols() != mc ) {
    return;
  }

  for ( unsigned int c = 0; c < mc; ++c ) {
    this->operator()( r, c ) = row( 0, c );
  }
}

/// @fn     void setRow( unsigned int r, vector<double> row )
/// @param  r     Row index
/// @param  row   Row vector
/// @brief  Set the row of the matrix with the provided data
void Matrix::setRow( unsigned int r, std::vector<double> row ) {
  if ( row.size() != mc ) {
    return;
  }

  for ( unsigned int c = 0; c < mc; ++c ) {
    this->operator()( r, c ) = row[c];
  }
}

/// @fn     void setCol( unsigned int c, Matrix column )
/// @param  c     Column index
/// @param  col   Column matrix
/// @brief  Set the column of the matrix with the provided data
void Matrix::setCol( unsigned int c, Matrix col ) {
  if ( col.rows() != mr ) {
    return;
  }

  for ( unsigned int r = 0; r < mr; ++r ) {
    this->operator()( r, c ) = col( r, 0 );
  }
}

/// @fn     void setCol( unsigned int c, vector<double> column )
/// @param  c     Column index
/// @param  col   Column vector
/// @brief  Set the column of the matrix with the provided data
void Matrix::setCol( unsigned int c, std::vector<double> col ) {
  if ( col.size() != mr ) {
    return;
  }

  for ( unsigned int r = 0; r < mr; ++r ) {
    this->operator()( r, c ) = col[r];
  }
}

/// @fn     void set( Matrix input )
/// @param  input   Input matrix
/// @brief  Set current matrix as copy of provided matrix
void Matrix::set( Matrix input ) {
  resize( input.rows(), input.cols() );
  this->operator=( input );
}

/// @fn     Matrix& transpose( void )
/// @brief  Generate a transpose of the current matrix
Matrix Matrix::transpose( void ) {
  Matrix output( mc, mr );
  for ( unsigned int r = 0; r < mr; ++r ) {
    for ( unsigned int c = 0; c < mc; ++c ) {
      output( c, r ) = this->operator()( r, c );
    }
  }
  return output;
}

/// @fn     void forEach( double ( *function )( double ) )
/// @param  function  Function Pointer
/// @brief  Run a function over all elements within the matrix
void Matrix::forEach( double ( *function )( double ) ) {
  for ( unsigned int i = 0; i < ( mr * mc ); ++i ) {
    mat[i] = function( mat[i] );
  }
}

/// @fn     double& operator()( unsigned int r, unsigned int c )
/// @param  r   Matrix row index
/// @param  c   Matrix column index
/// @brief  Matrix element selection using a 0 based index
double& Matrix::operator()( unsigned int r, unsigned int c ) {
  if ( r >= mr || c >= mc )
    return junk;
  unsigned int element = r + mr * c;
  return mat[element];
}

/// @fn     operator=( Matrix mat )
/// @param  mat   RHS matrix input
/// @brief  Set the matrix as the equivalent of the input matrix if they are
///         equivalent in structure
void Matrix::operator=( Matrix mat ) {
  if ( mr != mat.rows() || mc != mat.cols() ) {
    return;
  }

  for ( unsigned int r = 0; r < mr; ++r ) {
    for ( unsigned int c = 0; c < mc; ++c ) {
      this->operator()( r, c ) = mat( r, c );
    }
  }
}

/// @fn     operator=( vector<double> vec )
/// @param  vec   Vector input to be formatted
/// @brief  Convert the input vector into a matrix format with the current
///         matrix's structure
void Matrix::operator=( std::vector<double> vec ) {
  unsigned int elements = mr * mc;
  if ( elements != vec.size() ) {
    return;
  }

  unsigned int r = 0;
  unsigned int c = 0;
  for ( double element : vec ) {
    this->operator()( r, c ) = element;
    ++r;
    if ( r > mr ) {
      ++c;
    }
  }
}

/// @fn     Matrix operator+( Matrix rh )
/// @param  rh  Right-hand matrix element
/// @brief  Sum of two matrices
Matrix Matrix::operator+( Matrix rh ) {
  Matrix output( mr, mc );
  if ( mr != rh.rows() || mc != rh.cols() ) {
    return output;
  }

  for ( unsigned int r = 0; r < mr; ++r ) {
    for ( unsigned int c = 0; c < mc; ++c ) {
      output( r, c ) = this->operator()( r, c ) + rh( r, c );
    }
  }
  return output;
}

/// @fn     Matrix operator-( Matrix rh )
/// @param  rh  Right-hand matrix element
/// @brief  Difference of two matrices
Matrix Matrix::operator-( Matrix rh ) {
  Matrix output( mr, mc );
  if ( mr != rh.rows() || mc != rh.cols() ) {
    return output;
  }

  for ( unsigned int r = 0; r < mr; ++r ) {
    for ( unsigned int c = 0; c < mc; ++c ) {
      output( r, c ) = this->operator()( r, c ) - rh( r, c );
    }
  }
  return output;
}

/// @fn     Matrix operator*( Matrix rh )
/// @param  rh  Right-hand matrix element
/// @brief  Product of two matrices
Matrix Matrix::operator*( Matrix rh ) {
  Matrix output( mr, rh.cols() );
  if ( mc != rh.rows() )
    return output;

  for ( unsigned int c = 0; c < rh.cols(); ++c ) {
    for ( unsigned int r = 0; r < mr; ++r ) {
      double sum = 0;
      for ( unsigned int element = 0; element < mr; ++element ) {
        sum += getRow( r )( 0, element ) * rh.getCol( c )( element, 0 );
      }
      output( r, c ) = sum;
    }
  }
  return output;
}

/// @fn     Matrix operator/( Matrix rh )
/// @param  rh  Right-hand matrix element
/// @brief  Quotient of two matrices
/// TODO: Implement
Matrix Matrix::operator/( Matrix rh ) {
  return *this;
}

/// @fn     Matrix operator+( double rh )
/// @param  rh  Right-hand scalar element
/// @brief  Sum of a matrix and scalar value
Matrix Matrix::operator+( double rh ) {
  Matrix output( mr, mc );

  for ( unsigned int r = 0; r < mr; ++r ) {
    for ( unsigned int c = 0; c < mc; ++c ) {
      output( r, c ) = this->operator()( r, c ) + rh;
    }
  }
  return output;
}

/// @fn     Matrix operator-( double rh )
/// @param  rh  Right-hand scalar element
/// @brief  Difference of a matrix and scalar value
Matrix Matrix::operator-( double rh ) {
  Matrix output( mr, mc );

  for ( unsigned int r = 0; r < mr; ++r ) {
    for ( unsigned int c = 0; c < mc; ++c ) {
      output( r, c ) = this->operator()( r, c ) - rh;
    }
  }
  return output;
}

/// @fn     Matrix operator*( double rh )
/// @param  rh  Right-hand scalar element
/// @brief  Product of a matrix and scalar value
Matrix Matrix::operator*( double rh ) {
  Matrix output( mr, mc );

  for ( unsigned int r = 0; r < mr; ++r ) {
    for ( unsigned int c = 0; c < mc; ++c ) {
      output( r, c ) = this->operator()( r, c ) * rh;
    }
  }
  return output;
}

/// @fn     Matrix operator/( double rh )
/// @param  rh  Right-hand scalar element
/// @brief  Quotient of a matrix and scalar value
Matrix Matrix::operator/( double rh ) {
  Matrix output( mr, mc );

  for ( unsigned int r = 0; r < mr; ++r ) {
    for ( unsigned int c = 0; c < mc; ++c ) {
      output( r, c ) = this->operator()( r, c ) / rh;
    }
  }
  return output;
}

void Matrix::operator+=( Matrix rh ) {}
void Matrix::operator-=( Matrix rh ) {}
void Matrix::operator*=( Matrix rh ) {}
void Matrix::operator/=( Matrix rh ) {}
void Matrix::operator+=( double rh ) {}
void Matrix::operator-=( double rh ) {}
void Matrix::operator*=( double rh ) {}
void Matrix::operator/=( double rh ) {}

/// @fn     operator+( double lh, Matrix rh )
/// @param  lh  Left hand variable of operator
/// @param  rh  Right hand variable of operator
/// @brief  Sum of a matrix and a scalar where the scalar is the left hand
///         variable
Matrix operator+( double lh, Matrix rh ) {
  return rh + lh;
}

/// @fn     operator-( double lh, Matrix rh )
/// @param  lh  Left hand variable of operator
/// @param  rh  Right hand variable of operator
/// @brief  Difference of a matrix and a scalar where the scalar is the left
///         hand variable
Matrix operator-( double lh, Matrix rh ) {
  return -1 * ( rh - lh );
}

/// @fn     operator*( double lh, Matrix rh )
/// @param  lh  Left hand variable of operator
/// @param  rh  Right hand variable of operator
/// @brief  Product of a matrix and a scalar where the scalar is the left
///         hand variable
Matrix operator*( double lh, Matrix rh ) {
  return rh * lh;
}

/// @fn     operator/( double lh, Matrix rh )
/// @param  lh  Left hand variable of operator
/// @param  rh  Right hand variable of operator
/// @brief  Quotient of a matrix and a scalar where the scalar is the left
///         hand variable
Matrix operator/( double lh, Matrix rh ) {
  unsigned int mr = rh.rows();
  unsigned int mc = rh.cols();
  Matrix       output( mr, mc );

  for ( unsigned int r = 0; r < mr; ++r ) {
    for ( unsigned int c = 0; c < mc; ++c ) {
      output( r, c ) = lh / rh( r, c );
    }
  }
  return output;
}
