#include "utilities/matrix.h"

/// @fn     Matrix( void )
/// @brief  Initialize an empty 0-by-0 matrix
matrix::matrix( void ) {
  mr = 0;
  mc = 0;
  mat.clear();
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
/// @param  initMat Vector containing all elements in matrix
/// @brief  Initialize an r-by-c matrix set with provided elements
matrix::matrix( unsigned int r, unsigned int c, std::vector<double> initMat ) {
  resize( r, c, initMat );
}

/// @fn     ~Matrix( void )
/// @brief  Clear memory and reset values
matrix::~matrix( void ) {
  mat.clear();
}

void   matrix::reset( double initVal ) {}
void   matrix::clear( void ) {}
void   matrix::randomize( void ) {}
void   matrix::resize( unsigned int r, unsigned int c ) {}
void   matrix::resize( unsigned int r, unsigned int c, double initVal ) {}
void   matrix::resize( unsigned int        r,
                     unsigned int        c,
                     std::vector<double> initMat ) {}
matrix matrix::subMatrix( unsigned int r, unsigned int c ) {
  matrix temp;
  return temp;
}
matrix matrix::getRow( unsigned int r ) {
  matrix temp;
  return temp;
}
matrix matrix::getCol( unsigned int c ) {
  matrix temp;
  return temp;
}
void   matrix::setRow( unsigned int r, matrix row ) {}
void   matrix::setRow( unsigned int r, std::vector<double> row ) {}
void   matrix::setCol( unsigned int c, matrix col ) {}
void   matrix::setCol( unsigned int c, std::vector<double> col ) {}
void   matrix::set( matrix mat ) {}
matrix matrix::transpose( void ) {
  matrix temp;
  return temp;
}
double& matrix::operator()( unsigned int r, unsigned int c ) {
  return junk;
}
  void matrix::operator=( matrix mat ) {}
  void matrix::operator=( std::vector<double> mat ) {}
matrix matrix::operator+( matrix rh ) {
  matrix temp;
  return temp;
}
matrix matrix::operator-( matrix rh ) {
  matrix temp;
  return temp;
}
matrix matrix::operator*( matrix rh ) {
  matrix temp;
  return temp;
}
matrix matrix::operator/( matrix rh ) {
  matrix temp;
  return temp;
}
matrix matrix::operator+( double rh ) {
  matrix temp;
  return temp;
}
matrix matrix::operator-( double rh ) {
  matrix temp;
  return temp;
}
matrix matrix::operator*( double rh ) {
  matrix temp;
  return temp;
}
matrix matrix::operator/( double rh ) {
  matrix temp;
  return temp;
}
void matrix::operator+=( matrix rh ) {}
void matrix::operator-=( matrix rh ) {}
void matrix::operator*=( matrix rh ) {}
void matrix::operator/=( matrix rh ) {}
void matrix::operator+=( double rh ) {}
void matrix::operator-=( double rh ) {}
void matrix::operator*=( double rh ) {}
void matrix::operator/=( double rh ) {}
