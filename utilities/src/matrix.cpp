#include "utilities/matrix.h"
#include "utilities/random_number.h"

/// @fn     Matrix( void )
/// @brief  Initialize an empty 0-by-0 matrix
matrix::matrix( void ) {
  clear();
}

/// @fn     Matrix( unsigned int r, unsigned int c )
/// @param  r   Number of rows in matrix
/// @param  c   Number of columns in matrix
/// @brief  Initialize an empty r-by-c matrix
matrix::matrix( unsigned int r, unsigned int c ) {
  resize( r, c );
}

/// @fn     Matrix( unsigned int r, unsigned int c )
/// @param  r       Number of rows in matrix
/// @param  c       Number of columns in matrix
/// @param  initVal Initial value of all elements in matrix
/// @brief  Initialize an r-by-c matrix with all elments set to an initial value
matrix::matrix( unsigned int r, unsigned int c, double initVal ) {
  resize( r, c, initVal );
}

/// @fn     Matrix( unsigned int r, unsigned int c )
/// @param  r       Number of rows in matrix
/// @param  c       Number of columns in matrix
/// @param  initVec Vector containing all elements in matrix
/// @brief  Initialize an r-by-c matrix set with provided elements
matrix::matrix( unsigned int r, unsigned int c, std::vector<double> initVec ) {
  resize( r, c, initVec );
}

/// @fn     ~Matrix( void )
/// @brief  Clear memory and reset values
matrix::~matrix( void ) {
  clear();
}

/// @fn     void reset( double initVal )
/// @param  initVal   Desired initial value
/// @brief  Reset matrix and set every element in matrix to value provided
void matrix::reset( double initVal ) {
  if ( mr == 0 || mc == 0 ) {
    return;
  }

  for ( double& element : mat ) {
    element = initVal;
  }
}

/// @fn     void clear( void )
/// @brief  Clear the matrix of any data stored
void matrix::clear( void ) {
  mr = 0;
  mc = 0;
  mat.clear();
}

/// @fn     void randomize( void )
/// @brief  Set all elements in matrix to random values
void matrix::randomize( void ) {
  static RandomNumber rng;
  for ( double& element : mat )
    element = rng.random( -100, 100 );
}

/// @fn     void resize( unsigned int r, unsigned int c )
/// @param  r   Desired row count in resized matrix
/// @param  c   Desired column count in resized matrix
/// @brief  Resize the matrix to a new desired size. Removes all data currently
///         in matrix
void matrix::resize( unsigned int r, unsigned int c ) {
  resize( r, c, 0.0 );
}

/// @fn     void resize( unsigned int r, unsigned int c, double initVal )
/// @param  r         Desired row count in resized matrix
/// @param  c         Desired column count in resized matrix
/// @param  initVal   Initial value to set matrix elements
/// @brief  Resize the matrix to a new desired size. Removes all data currently
///         in matrix
void matrix::resize( unsigned int r, unsigned int c, double initVal ) {
  unsigned int totalElements = r * c;
  mat.resize( totalElements );

  mr = r;
  mc = c;

  reset( initVal );
}

/// @fn     void resize( unsigned int r, unsigned int c, vector<double> initVal
/// )
/// @param  r         Desired row count in resized matrix
/// @param  c         Desired column count in resized matrix
/// @param  initVec   Initial vector of values to set matrix elements
/// @brief  Resize the matrix to a new desired size. Removes all data currently
///         in matrix
void matrix::resize( unsigned int        r,
                     unsigned int        c,
                     std::vector<double> initVec ) {
  unsigned int totalElements = r * c;
  if ( ( initVec.size() != totalElements ) || ( totalElements == 0 ) ) {
    return;
  }
  mat.resize( totalElements );

  mr = r;
  mc = c;

  for ( unsigned int iter = 0; iter < totalElements; ++iter ) {
    mat[iter] = initVec[iter];
  }
}

matrix matrix::subMatrix( unsigned int r, unsigned int c ) {
  return *this;
}
matrix matrix::getRow( unsigned int r ) {
  return *this;
}
matrix matrix::getCol( unsigned int c ) {
  return *this;
}
void matrix::setRow( unsigned int r, matrix row ) {}
void matrix::setRow( unsigned int r, std::vector<double> row ) {}
void matrix::setCol( unsigned int c, matrix col ) {}
void matrix::setCol( unsigned int c, std::vector<double> col ) {}

/// @fn     void set( matrix input )
/// @param  input   Input matrix
/// @brief  Set current matrix as copy of provided matrix
void matrix::set( matrix input ) {
  resize( input.rows(), input.cols() );
  this->operator=( input );
}

/// @fn     matrix transpose( void )
/// @brief  Generate a transpose of the current matrix
matrix matrix::transpose( void ) {
  matrix temp( mc, mr );
  for ( unsigned int r = 0; r < mr; ++r ) {
    for ( unsigned int c = 0; c < mc; ++c ) {
      temp( c, r ) = this->operator()( r, c );
    }
  }
  return temp;
}

/// @fn     double& operator()( unsigned int r, unsigned int c )
/// @param  r   Matrix row index
/// @param  c   Matrix column index
/// @brief  Matrix element selection using a 0 based index
double& matrix::operator()( unsigned int r, unsigned int c ) {
  if ( r >= mr || c >= mc )
    return junk;
  unsigned int element = r + mr * c;
  return mat[element];
}

/// @fn     operator=( matrix mat )
/// @param  mat   RHS matrix input
/// @brief  Set the matrix as the equivalent of the input matrix if they are
///         equivalent in structure
void matrix::operator=( matrix mat ) {
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
void matrix::operator=( std::vector<double> vec ) {
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

/// @fn     matrix operator+( matrix rh )
/// @param  rh  Right-hand matrix element
/// @brief  Matrix addition of two matrices
matrix matrix::operator+( matrix rh ) {
  matrix output( mr, mc );
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

/// @fn     matrix operator-( matrix rh )
/// @param  rh  Right-hand matrix element
/// @brief  Matrix subtraction of two matrices
matrix matrix::operator-( matrix rh ) {
  matrix output( mr, mc );
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
matrix matrix::operator*( matrix rh ) {
  return *this;
}
matrix matrix::operator/( matrix rh ) {
  return *this;
}

/// @fn     matrix operator+( double rh )
/// @param  rh  Right-hand scalar element
/// @brief  Matrix addition with a scalar value
matrix matrix::operator+( double rh ) {
  matrix output( mr, mc );

  for ( unsigned int r = 0; r < mr; ++r ) {
    for ( unsigned int c = 0; c < mc; ++c ) {
      output( r, c ) = this->operator()( r, c ) + rh;
    }
  }
  return output;
}

/// @fn     matrix operator-( double rh )
/// @param  rh  Right-hand scalar element
/// @brief  Matrix subtraction with a scalar value
matrix matrix::operator-( double rh ) {
  matrix output( mr, mc );

  for ( unsigned int r = 0; r < mr; ++r ) {
    for ( unsigned int c = 0; c < mc; ++c ) {
      output( r, c ) = this->operator()( r, c ) - rh;
    }
  }
  return output;
}

/// @fn     matrix operator*( double rh )
/// @param  rh  Right-hand scalar element
/// @brief  Matrix multiplication with a scalar value
matrix matrix::operator*( double rh ) {
  matrix output( mr, mc );

  for ( unsigned int r = 0; r < mr; ++r ) {
    for ( unsigned int c = 0; c < mc; ++c ) {
      output( r, c ) = this->operator()( r, c ) * rh;
    }
  }
  return output;
}

/// @fn     matrix operator/( double rh )
/// @param  rh  Right-hand scalar element
/// @brief  Matrix division with a scalar value
matrix matrix::operator/( double rh ) {
  matrix output( mr, mc );

  for ( unsigned int r = 0; r < mr; ++r ) {
    for ( unsigned int c = 0; c < mc; ++c ) {
      output( r, c ) = this->operator()( r, c ) / rh;
    }
  }
  return output;
}

void matrix::operator+=( matrix rh ) {}
void matrix::operator-=( matrix rh ) {}
void matrix::operator*=( matrix rh ) {}
void matrix::operator/=( matrix rh ) {}
void matrix::operator+=( double rh ) {}
void matrix::operator-=( double rh ) {}
void matrix::operator*=( double rh ) {}
void matrix::operator/=( double rh ) {}

matrix operator+( double lh, matrix rh ) {
  unsigned int mr = rh.rows();
  unsigned int mc = rh.cols();
  matrix       output( mr, mc );

  for ( unsigned int r = 0; r < mr; ++r ) {
    for ( unsigned int c = 0; c < mc; ++c ) {
      output( r, c ) = lh + rh( r, c );
    }
  }
  return output;
}

matrix operator-( double lh, matrix rh ) {
  unsigned int mr = rh.rows();
  unsigned int mc = rh.cols();
  matrix       output( mr, mc );

  for ( unsigned int r = 0; r < mr; ++r ) {
    for ( unsigned int c = 0; c < mc; ++c ) {
      output( r, c ) = lh - rh( r, c );
    }
  }
  return output;
}

matrix operator*( double lh, matrix rh ) {
  unsigned int mr = rh.rows();
  unsigned int mc = rh.cols();
  matrix       output( mr, mc );

  for ( unsigned int r = 0; r < mr; ++r ) {
    for ( unsigned int c = 0; c < mc; ++c ) {
      output( r, c ) = lh * rh( r, c );
    }
  }
  return output;
}

matrix operator/( double lh, matrix rh ) {
  unsigned int mr = rh.rows();
  unsigned int mc = rh.cols();
  matrix       output( mr, mc );

  for ( unsigned int r = 0; r < mr; ++r ) {
    for ( unsigned int c = 0; c < mc; ++c ) {
      output( r, c ) = lh / rh( r, c );
    }
  }
  return output;
}
