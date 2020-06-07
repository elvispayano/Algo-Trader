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

template<typename T>
class Matrix {
public:
  // Constructors
  Matrix(void);
  Matrix(size_t r, size_t c, T val = 0.0);

  // Destructor
  ~Matrix(void);

  // Reset all element in matrix
  void clear(T initVal = 0.0);

  // Reshape and reset matrix
  void resize(size_t r, size_t c, T initVal = 0.0);

  // Get matrix size info
  size_t rows(void) { return mr; }
  size_t cols(void) { return mc; }

  // Get specific vector from within matrix
  Matrix<T> getRow(size_t r);
  Matrix<T> getCol(size_t c);
  
  // Process functions over all elements
  void forEach(T(*func)(T));
  void forEach(T(*func)(T, T), T scalar);
  Matrix<T> forEach(T(*func)(T, T), Matrix<T> inp);

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
  size_t mr; // Matrix row size
  size_t mc; // Matrix col size

  T* mat; // Matrix array pointer

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
  mat = nullptr;
  resize(1, 1, 0);
}

template<typename T>
Matrix<T>::Matrix(size_t r, size_t c, T val = 0) {
  mat = nullptr;
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
  //if (mat) delete[] mat; mat = nullptr;
}

/*
  Function:   Clear
  Inputs:     initVal

  Description:
    Reset all elements within the matrix to the designated
    initial value.
*/
template<typename T>
void Matrix<T>::clear(T initVal = 0) {
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
  if (mat) delete[] mat; mat = nullptr;
  mat = new T[mr * mc];
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
  Function:   For Each
  Inputs:     Varies:
                T func(T)
                T func(T,T) & input  [Matrix<T>]
                T func(T,T) & scalar [T]
  Description:
    Run function through every element within the matrix
*/
template<typename T>
void Matrix<T>::forEach(T(*func)(T)) {
  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      this->operator()(r, c) = func(this->operator()(r, c));
    }
  }
}

template<typename T>
void Matrix<T>::forEach(T(*func)(T, T), T scalar) {
  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      this->operator()(r, c) = func(this->operator()(r, c), scalar);
    }
  }
}

template<typename T>
Matrix<T> Matrix<T>::forEach(T(*func)(T, T), Matrix<T> inp) {
  Matrix<T> output(mr, mc, 0.0);
  if (mr != inp.rows()) return output;
  if (mc != inp.cols()) return output;

  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      output(r, c) = func(this->operator()(r, c), inp(r, c));
    }
  }
  return output;
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
  return mat[r + mc * c];
}

/*
  Operator:   =
  Inputs:     Input (Matrix<T>)

  Description:
    Assign values of input matrix into self if sizes match
*/
template<typename T>
void Matrix<T>::operator=(Matrix<T> inp) {
  if (mr != inp.rows()) return;
  if (mc != inp.cols()) return;

  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      this->operator()(r, c) = inp(r, c);
    }
  }
}

template<typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T> inp) {
  auto lambda = [](T x, T y)->T { return x + y; };
  Matrix<T> output = forEach(lambda, inp);
  return output;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(T scalar) {
  Matrix<T> Output(mr, mr);
  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      Output(r, c) = this->operator()(r, c) + scalar;
    }
  }
  return Output;
}

template<typename T>
void Matrix<T>::operator+=(Matrix<T> inp) {
  if (mr != inp.rows()) return;
  if (mc != inp.cols()) return;

  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      this->operator()(r, c) += inp(r, c);
    }
  }
}

template<typename T>
void Matrix<T>::operator+=(T scalar) {
  auto lambda = [](T x, T y)->T { return x + y; };
  forEach(lambda, scalar);
}

template<typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T> inp) {
  auto lambda = [](T x, T y)->T { return x - y; };
  Matrix<T> output = forEach(lambda, inp);
  return output;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(T scalar) {
  Matrix<T> Output(mr, mr);
  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      Output(r, c) = this->operator()(r, c) - scalar;
    }
  }
  return Output;
}

template<typename T>
void Matrix<T>::operator-=(Matrix<T> inp) {
  if (mr != inp.rows()) return;
  if (mc != inp.cols()) return;

  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      this->operator()(r, c) -= inp(r, c);
    }
  }
}

template<typename T>
void Matrix<T>::operator-=(T scalar) {
  auto lambda = [](T x, T y)->T { return x - y; };
  forEach(lambda, scalar);
}

template<typename T>
Matrix<T> Matrix<T>::operator*(T scalar) {
  Matrix<T> Output(mr, mr, 0.0);
  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      Output(r, c) = this->operator()(r, c) * scalar;
    }
  }
  return Output;
}

template<typename T>
Matrix<T> Matrix<T>::operator/(T scalar) {
  Matrix<T> Output(mr, mr, 0.0);
  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      Output(r, c) = this->operator()(r, c) / scalar;
    }
  }
  return Output;
}

template<typename T>
void Matrix<T>::operator*=(T scalar) {
  auto lambda = [](T x, T y)->T { return x * y; };
  forEach(lambda, scalar);
}

template<typename T>
void Matrix<T>::operator/=(T scalar) {
  auto lambda = [](T x, T y)->T { return x / y; };
  forEach(lambda, scalar);
}

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

template<typename T>
void Matrix<T>::operator*=(Matrix<T> inp) {
  if (mc != inp.rows()) return;
  Matrix<T> out(this->operator*(inp));
  resize(out.rows(), out.cols());
  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      this->operator()(r, c) = out(r, c);
    }
  }
}

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

//----------------------------------------------------------------
// Common Typedefs
//----------------------------------------------------------------
typedef Matrix<double> dMatrix;
typedef Matrix<int>    iMatrix;
typedef Matrix<float>  fMatrix;

#endif // MATRIX_H
