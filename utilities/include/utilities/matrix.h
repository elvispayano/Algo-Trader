/// Matrix
///
/// Functionality for processing matrix data
///
/// \author   Elvis Payano
/// \date     18/09/2020
/// \version  0.0.1

#ifndef MATRIX_H
#define MATRIX_H

// Standard Includes
#include <vector>

class Matrix {
public:
  /// @fn     Matrix( void )
  /// @brief  Initialize an empty 0-by-0 matrix
  Matrix( void );

  /// @fn     Matrix( const Matrix& in )
  /// @brief  Copy constructor
  Matrix( const Matrix& in );

  /// @fn     Matrix( unsigned int r, unsigned int c )
  /// @param  r   Number of rows in matrix
  /// @param  c   Number of columns in matrix
  /// @brief  Initialize an empty r-by-c matrix
  Matrix( unsigned int r, unsigned int c );

  /// @fn     Matrix( unsigned int r, unsigned int c )
  /// @param  r       Number of rows in matrix
  /// @param  c       Number of columns in matrix
  /// @param  initVal Initial value of all elements in matrix
  /// @brief  Initialize an r-by-c matrix with all elments set to an initial
  /// value
  Matrix( unsigned int r, unsigned int c, double initVal );

  /// @fn     Matrix( unsigned int r, unsigned int c )
  /// @param  r       Number of rows in matrix
  /// @param  c       Number of columns in matrix
  /// @param  initVec Vector containing all elements in matrix
  /// @brief  Initialize an r-by-c matrix set with provided elements
  Matrix( unsigned int r, unsigned int c, double* initVec );

  /// @fn     ~Matrix( void )
  /// @brief  Clear memory and reset values
  ~Matrix( void );

  /// @fn     void reset( double initVal )
  /// @param  initVal   Desired initial value
  /// @brief  Reset matrix and set every element in matrix to value provided
  void reset( double initVal );

  /// @fn     void clear( void )
  /// @brief  Clear the matrix of any data stored
  void clear( void );

  /// @fn     void randomize( void )
  /// @brief  Set all elements in matrix to random values
  void randomize( void );

  /// @fn     void resize( unsigned int r, unsigned int c )
  /// @param  r   Desired row count in resized matrix
  /// @param  c   Desired column count in resized matrix
  /// @brief  Resize the matrix to a new desired size. Removes all data
  ///         currently in matrix
  void resize( unsigned int r, unsigned int c );

  /// @fn     void resize( unsigned int r, unsigned int c, double initVal )
  /// @param  r         Desired row count in resized matrix
  /// @param  c         Desired column count in resized matrix
  /// @param  initVal   Initial value to set matrix elements
  /// @brief  Resize the matrix to a new desired size. Removes all data
  ///         currently in matrix
  void resize( unsigned int r, unsigned int c, double initVal );

  /// @fn     void resize( unsigned int r, unsigned int c, vector<double>
  ///                      initVal )
  /// @param  r         Desired row count in resized matrix
  /// @param  c         Desired column count in resized matrix
  /// @param  initVec   Initial vector of values to set matrix elements
  /// @brief  Resize the matrix to a new desired size. Removes all data
  ///         currently in matrix
  void resize( unsigned int r, unsigned int c, double* initMat );

  /// @fn     void rows( void )
  /// @brief  Get the number of rows present in the matrix
  unsigned int rows( void ) { return mr; }

  /// @fn     void cols( void )
  /// @brief  Get the number of columns present in the matrix
  unsigned int cols( void ) { return mc; }

  /// @fn     Matrix subMatrix( unsigned int r, unsigned int c )
  /// @param  r   Row index
  /// @param  c   Column index
  /// @brief  Return a matrix that contains all elements minus what is present
  ///         in the row and column indeces provided
  Matrix subMatrix( unsigned int r, unsigned int c );

  /// @fn     Matrix getRow( unsigned int r )
  /// @param  r   Row index
  /// @brief  Get a single row from within the matrix
  Matrix getRow( unsigned int r );

  /// @fn     Matrix getCol( unsigned int c )
  /// @param  c   Column index
  /// @brief  Get a single column from within the matrix
  Matrix getCol( unsigned int c );

  /// @fn     void setRow( unsigned int r, Matrix row )
  /// @param  r     Row index
  /// @param  row   Row matrix
  /// @brief  Set the row of the matrix with the provided data
  void setRow( unsigned int r, Matrix row );

  /// @fn     void setRow( unsigned int r, vector<double> row )
  /// @param  r     Row index
  /// @param  row   Row vector
  /// @brief  Set the row of the matrix with the provided data
  void setRow( unsigned int r, std::vector<double> row );

  /// @fn     void setCol( unsigned int c, Matrix column )
  /// @param  c     Column index
  /// @param  col   Column matrix
  /// @brief  Set the column of the matrix with the provided data
  void setCol( unsigned int c, Matrix col );

  /// @fn     void setCol( unsigned int c, vector<double> column )
  /// @param  c     Column index
  /// @param  col   Column vector
  /// @brief  Set the column of the matrix with the provided data
  void setCol( unsigned int c, std::vector<double> col );

  /// @fn     void set( Matrix input )
  /// @param  input   Input matrix
  /// @brief  Set current matrix as copy of provided matrix
  void set( Matrix input );

  /// @fn     Matrix transpose( void )
  /// @brief  Generate a transpose of the current matrix
  Matrix transpose();

  /// @fn     void forEach( double ( *function )( double ) )
  /// @param  function  Function Pointer
  /// @brief  Run a function over all elements within the matrix
  void forEach( double ( *function )( double ) );

  /// @fn     double& operator()( unsigned int r, unsigned int c )
  /// @param  r   Matrix row index
  /// @param  c   Matrix column index
  /// @brief  Matrix element selection using a 0 based index
  double& operator()( unsigned int r, unsigned int c );

  /// @fn     operator=( Matrix mat )
  /// @param  mat   RHS matrix input
  /// @brief  Set the matrix as the equivalent of the input matrix if they are
  ///         equivalent in structure
  void operator=( Matrix mat );

  /// @fn     operator=( vector<double> vec )
  /// @param  vec   Vector input to be formatted
  /// @brief  Convert the input vector into a matrix format with the current
  ///         matrix's structure
  void operator=( std::vector<double> mat );

  /// @fn     Matrix operator+( Matrix rh )
  /// @param  rh  Right-hand matrix element
  /// @brief  Sum of two matrices
  Matrix operator+( Matrix rh );

  /// @fn     Matrix operator-( Matrix rh )
  /// @param  rh  Right-hand matrix element
  /// @brief  Difference of two matrices
  Matrix operator-( Matrix rh );

  /// @fn     Matrix operator*( Matrix rh )
  /// @param  rh  Right-hand matrix element
  /// @brief  Product of two matrices
  Matrix operator*( Matrix rh );

  /// @fn     Matrix operator/( Matrix rh )
  /// @param  rh  Right-hand matrix element
  /// @brief  Quotient of two matrices
  Matrix operator/( Matrix rh );

  /// @fn     Matrix operator+( double rh )
  /// @param  rh  Right-hand scalar element
  /// @brief  Sum of a matrix and scalar value
  Matrix operator+( double rh );

  /// @fn     Matrix operator-( double rh )
  /// @param  rh  Right-hand scalar element
  /// @brief  Matrix subtraction with a scalar value
  Matrix operator-( double rh );

  /// @fn     Matrix operator*( double rh )
  /// @param  rh  Right-hand scalar element
  /// @brief  Product of a matrix and scalar value
  Matrix operator*( double rh );

  /// @fn     Matrix operator/( double rh )
  /// @param  rh  Right-hand scalar element
  /// @brief  Quotient of a matrix and scalar value
  Matrix operator/( double rh );

  void operator+=( Matrix rh );
  void operator-=( Matrix rh );
  void operator*=( Matrix rh );
  void operator/=( Matrix rh );

  void operator+=( double rh );
  void operator-=( double rh );
  void operator*=( double rh );
  void operator/=( double rh );

private:
  unsigned int mr;
  unsigned int mc;

  double junk = 0;

  double* mat;
};

/// @fn     operator+( double lh, Matrix rh )
/// @param  lh  Left hand variable of operator
/// @param  rh  Right hand variable of operator
/// @brief  Sum of a matrix and a scalar where the scalar is the left hand
///         variable
Matrix operator+( double lh, Matrix rh );

/// @fn     operator-( double lh, Matrix rh )
/// @param  lh  Left hand variable of operator
/// @param  rh  Right hand variable of operator
/// @brief  Difference of a matrix and a scalar where the scalar is the left
///         hand variable
Matrix operator-( double lh, Matrix rh );

/// @fn     operator*( double lh, Matrix rh )
/// @param  lh  Left hand variable of operator
/// @param  rh  Right hand variable of operator
/// @brief  Product of a matrix and a scalar where the scalar is the left
///         hand variable
Matrix operator*( double lh, Matrix rh );

/// @fn     operator/( double lh, Matrix rh )
/// @param  lh  Left hand variable of operator
/// @param  rh  Right hand variable of operator
/// @brief  Quotient of a matrix and a scalar where the scalar is the left
///         hand variable
Matrix operator/( double lh, Matrix rh );

#endif  // MATRIX_H
