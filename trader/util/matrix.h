/*
  Title:
    Matrix

  Description:
    This matrix template class contains all the functionality
    for processing matrix data.

  Tests:
    test_matrix.cc

  Author:
    Elvis Payano
*/

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

template<typename T>
class Matrix {
public:
  // Constructors
  Matrix(void);
  Matrix(size_t r, size_t c, T val);

  // Destructor
  ~Matrix(void);

  // Reset all element in matrix
  void clear(T initVal);

  // Reshape and reset matrix
  void resize(size_t r, size_t c, T initVal);

  // Get matrix size info
  size_t rows(void) { return mr; }
  size_t cols(void) { return mc; }

  // Get specific vector from within matrix
  Matrix<T> getRow(size_t r);
  Matrix<T> getCol(size_t c);
  
  // Process functions over all elements
  void forEach(T(*func)(T));

  // Matrix For Each
  void forEach(T(*func)(T, T), Matrix<T> in, Matrix<T>& out);
  void forEach(T(*func)(T, T), Matrix<T> in);

  // Scalar For Each
  void forEach(T(*func)(T, T), T in, Matrix<T>& out);
  void forEach(T(*func)(T, T), T in);

  // Get submatrix that does not include elements from
  // row (r) or column (c)
  Matrix<T> subMatrix(size_t r, size_t c);

  // Operators
  T& operator()(size_t r, size_t c);

  // Matrix Arithmetic
  void operator=(Matrix<T>);
  Matrix<T> operator+(Matrix<T>);
  Matrix<T> operator-(Matrix<T>);
  Matrix<T> operator*(Matrix<T>);

  // Matrix Arithmetic & Assignment
  void operator+=(Matrix<T>);
  void operator-=(Matrix<T>);
  void operator*=(Matrix<T>);

  // Scalar Arithmetic
  Matrix<T> operator+(T);
  Matrix<T> operator-(T);
  Matrix<T> operator*(T);
  Matrix<T> operator/(T);

  // Scalar Arithmetic & Assignment
  void operator+=(T);
  void operator-=(T);
  void operator*=(T);
  void operator/=(T);

private:
  size_t mr = 0; // Matrix row size
  size_t mc = 0; // Matrix col size

  std::vector<T> mat;

  // Junk value to return if attempting to address matrix
  // from out of bounds
  T junk = 0;
};

/*
  Constructors:   Matrix
  Inputs:         (None) or (rows [size_t], cols [size_t], initial_value [T])

  Description:
    Generate matrix object with the specified attributes
    or default to a 1x1 matrix with a 0 value
*/
template<typename T>
Matrix<T>::Matrix(void) {
  mat.clear();
  resize(1, 1, 0);
}

template<typename T>
Matrix<T>::Matrix(size_t r, size_t c, T val) {
  mat.clear();
  resize(r, c, val);
}

/*
  Destructor: ~Matrix
  Inputs:     None (void)

  Description:
    Delete allocted array that contains matrix.
*/
template<typename T>
Matrix<T>::~Matrix(void) {
  mat.clear();
}

/*
  Function:   Clear
  Inputs:     initVal

  Description:
    Reset all elements within the matrix to the designated
    initial value.
*/
template<typename T>
void Matrix<T>::clear(T initVal) {
  auto lambda = [](T x, T y)->T { return y; };
  forEach(lambda, initVal);
}

/*
  Function:   Resize
  Inputs:     rows (size_t), cols (size_t), initial_value (T)

  Description:
    Reshape matrix to desired size. Reshaping destroys the previous
    matrix and as such those values will not be retained.
*/
template<typename T>
void Matrix<T>::resize(size_t r, size_t c, T val) {
  if (r == 0) return;
  if (c == 0) return;
  mr = r; mc = c;

  mat.clear();
  mat.resize(mr * mc);
  clear(val);
}

/*
  Function:   Get Row
  Inputs:     row (size_t)
  Output:     Row Matrix (Matrix<T>)

  Description:
    Return a single row matrix with all elements from requested
    row
*/
template<typename T>
Matrix<T> Matrix<T>::getRow(size_t r) {
  Matrix<T> Output(1, mc, 0.0);
  for (size_t c = 0; c < mc; ++c) {
    Output(0, c) = this->operator()(r, c);
  }
  return Output;
}

/*
  Function:   Get Col
  Inputs:     col (size_t)
  Output:     Column Matrix (Matrix<T>)

  Description:
    Return a single column matrix with all elements from requested
    column
*/
template<typename T>
Matrix<T> Matrix<T>::getCol(size_t c) {
  Matrix<T> Output(mr, 1, 0.0);
  for (size_t r = 0; r < mr; ++r) {
    Output(r, 0) = this->operator()(r,c);
  }
  return Output;
}

/*
  Function:   subMatrix
  Inputs:     row (size_t), col (size_t)
  Output:     Matrix (Matrix<T>)

  Description:
    Return a matrix of size (mr-1)x(mc-1) that contains all elements of
    original matrix except for those found in the row & col provided
*/
template<typename T>
Matrix<T> Matrix<T>::subMatrix(size_t r, size_t c) {
  Matrix<T> Output(mr - 1, mc - 1, 0.0);
  size_t sr = 0;
  size_t sc = 0;
  for (size_t row = 0; row < mr; ++row) {
    for (size_t col = 0; col < mc; ++col) {
      if (row == r || col == c) continue;
      Output(sr++, sc++) = this->operator()(row, col);
    }
  }
  return Output;
}

/*
  Function:   For Each
  Inputs:   T(*func)(T)

  Description
    Run function with every element of matrix as input and assign
    to current element
*/
template<typename T>
void Matrix<T>::forEach(T(*func)(T)) {
  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      this->operator()(r, c) = func(this->operator()(r, c));
    }
  }
}

/*
  Function:   For Each
  Inputs:   T(*func)(T x , T y), Matrix<T> in, Matrix<T>& out
  
  Description:
    Run function on every element with "self" elements as x and "in"
    elements as y. Output is captured using the "out" entry
*/
template<typename T>
void Matrix<T>::forEach(T(*func)(T, T), Matrix<T> in, Matrix<T>& out) {
  if (mr != in.rows()) return;
  if (mc != in.cols()) return;

  if (mr != out.rows()) return;
  if (mc != out.cols()) return;

  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      out(r, c) = func(this->operator()(r, c), in(r, c));
    }
  }
}

/*
  Function:   For Each
  Inputs:   T(*func)(T x , T y), Matrix<T> in

  Description:
    Run function on every element with "self" elements as x and "in"
    elements as y. Output is assigned to "self" current element
*/
template<typename T>
void Matrix<T>::forEach(T(*func)(T, T), Matrix<T> in) {
  if (mr != in.rows()) return;
  if (mc != in.cols()) return;

  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      this->operator()(r, c) = func(this->operator()(r, c), in(r, c));
    } 
  }
}

/*
  Function:   For Each
  Inputs:   T(*func)(T x , T y), T in, Matrix<T>& out

  Description:
    Run function on every element with "self" elements as x and "in"
    y. Output is captured using the "out" entry
*/
template<typename T>
void Matrix<T>::forEach(T(*func)(T, T), T in, Matrix<T>& out) {
  if (mr != out.rows()) return;
  if (mc != out.cols()) return;

  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      out(r, c) = func(this->operator()(r, c), in);
    }
  }
}

/*
  Function:   For Each
  Inputs:   T(*func)(T x , T y), T in

  Description:
    Run function on every element with "self" elements as x and "in"
    y. Output is assigned to "self" current element
*/
template<typename T>
void Matrix<T>::forEach(T(*func)(T, T), T in) {
  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      this->operator()(r, c) = func(this->operator()(r, c), in);
    }
  }
}

/*
  Operator:   ()
  Inputs:     r (size_t), c (size_t)
  Output:     Matrix element (T&)

  Description:
    Access matrix elements using zero base indexing. Attempting
    to access an index outside of the matrix size will result in
    unwanted values.
*/
template<typename T>
T& Matrix<T>::operator()(size_t r, size_t c) {
  if (r >= mr) return junk;
  if (c >= mc) return junk;
  return mat[r + mr * c];
}

/*
  Operator:   =
  Inputs:     Input (Matrix<T>)

  Description:
    Assign values of input matrix into self if sizes match
*/
template<typename T>
void Matrix<T>::operator=(Matrix<T> inp) {
  auto lambda = [](T x, T y)->T { return y; };
  forEach(lambda, inp);
}

/*
  Operator:   +
  Input:      Input (Matrix<T>)
  Output:     Output (Matrix<T>)

  Description:
    Add contents of current matrix and input matrix
    and return within output matrix
*/
template<typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T> inp) {
  auto lambda = [](T x, T y)->T { return x + y; };
  Matrix<T> output(mr, mc, 0.0);
  
  forEach(lambda, inp, output);
  return output;
}

/*
  Operator:   -
  Input:      Input (Matrix<T>)
  Output:     Output (Matrix<T>)

  Description:
    Subtract contents of current matrix and input matrix
    and return within output matrix
*/
template<typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T> inp) {
  auto lambda = [](T x, T y)->T { return x - y; };
  Matrix<T> output(mr, mc, 0.0);

  forEach(lambda, inp, output);
  return output;
}

/*
  Operator:   *
  Input:      Input (Matrix<T>)
  Output:     Output (Matrix<T>)

  Description:
    Perform matrix multiplication and output matrix
*/
template<typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T> inp) {
  Matrix<T> Output(mr, inp.cols(), 0.0);
  if (mc != inp.rows()) return Output;
  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < inp.cols(); ++c) {
      T sum = 0;
      for (size_t x = 0; x < mr; ++x) sum += getRow(r)(0, x) * inp.getCol(c)(x, 0);
      Output(r, c) = sum;
    }
  }
  return Output;
}

/*
  Operator:   +
  Input:      Input (T)
  Output:     Output (Matrix<T>)

  Description:
    Add scalar to every element of current matrix
    and return within output matrix
*/
template<typename T>
Matrix<T> Matrix<T>::operator+(T scalar) {
  auto lambda = [](T x, T y)->T { return x + y; };
  Matrix<T> output(mr, mc, 0.0);

  forEach(lambda, scalar, output);
  return output;
}

/*
  Operator:   -
  Input:      Input (T)
  Output:     Output (Matrix<T>)

  Description:
    Subtract scalar to every element of current matrix
    and return within output matrix
*/
template<typename T>
Matrix<T> Matrix<T>::operator-(T scalar) {
  auto lambda = [](T x, T y)->T { return x - y; };
  Matrix<T> output(mr, mc, 0.0);

  forEach(lambda, scalar, output);
  return output;
}

/*
  Operator:   *
  Input:      Input (T)
  Output:     Output (Matrix<T>)

  Description:
    Multiply scalar to every element of current matrix
    and return within output matrix
*/
template<typename T>
Matrix<T> Matrix<T>::operator*(T scalar) {
  auto lambda = [](T x, T y)->T { return x * y; };
  Matrix<T> output(mr, mc, 0.0);

  forEach(lambda, scalar, output);
  return output;
}

/*
  Operator:   /
  Input:      Input (T)
  Output:     Output (Matrix<T>)

  Description:
    Divide every element of current matrix with a scalar
    and return within output matrix
*/
template<typename T>
Matrix<T> Matrix<T>::operator/(T scalar) {
  auto lambda = [](T x, T y)->T { return x / y; };
  Matrix<T> output(mr, mc, 0.0);

  forEach(lambda, scalar, output);
  return output;
}

/*
  Operator:   +=
  Input:      Input (Matrix<T>)

  Description:
    Add contents of input matrix into current matrix
*/
template<typename T>
void Matrix<T>::operator+=(Matrix<T> inp) {
  auto lambda = [](T x, T y)->T { return x + y; };
  forEach(lambda, inp);
}

/*
  Operator:   -=
  Input:      Input (Matrix<T>)

  Description:
    Subtract contents of input matrix from current matrix
*/
template<typename T>
void Matrix<T>::operator-=(Matrix<T> inp) {
  auto lambda = [](T x, T y)->T { return x - y; };
  forEach(lambda, inp);
}

/*
  Operator:   *=
  Input:      Input (Matrix<T>)

  Description:
    Perform matrix multiplication
*/
template<typename T>
void Matrix<T>::operator*=(Matrix<T> inp) {
  if (mc != inp.rows()) return;
  Matrix<T> out(this->operator*(inp));
  resize(out.rows(), out.cols(), 0.0);
  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      this->operator()(r, c) = out(r, c);
    }
  }
}

/*
  Operator:   +=
  Input:      Input (T)

  Description:
    Add scalar to every element of current matrix
*/
template<typename T>
void Matrix<T>::operator+=(T scalar) {
  auto lambda = [](T x, T y)->T { return x + y; };
  forEach(lambda, scalar);
}

/*
  Operator:   -=
  Input:      Input (T)

  Description:
    Subtract scalar from every element of current matrix
*/
template<typename T>
void Matrix<T>::operator-=(T scalar) {
  auto lambda = [](T x, T y)->T { return x - y; };
  forEach(lambda, scalar);
}

/*
  Operator:   *=
  Input:      Input (T)

  Description:
    Multiply scalar with every element of current matrix
*/
template<typename T>
void Matrix<T>::operator*=(T scalar) {
  auto lambda = [](T x, T y)->T { return x * y; };
  forEach(lambda, scalar);
}

/*
  Operator:   /=
  Input:      Input (T)

  Description:
    Divide every element in current matrix by scalar
*/
template<typename T>
void Matrix<T>::operator/=(T scalar) {
  auto lambda = [](T x, T y)->T { return x / y; };
  forEach(lambda, scalar);
}

typedef Matrix<double> dMatrix;
typedef Matrix<int>    iMatrix;
typedef Matrix<float>  fMatrix;

#endif // MATRIX_H
