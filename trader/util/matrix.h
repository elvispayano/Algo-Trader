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

  void Clear(T = 0.0);
  void Resize(size_t r, size_t c, T val = 0.0);
  size_t Rows(void) { return mr; }
  size_t Cols(void) { return mc; }

  Matrix<T> GetRow(size_t r);
  Matrix<T> GetCol(size_t c);
  
  Matrix<T> forEach(double(*func)(double));

  T Determinant(void);
  Matrix<T> SubMatrix(size_t r, size_t c);

  // Operators
  T& operator()(size_t r, size_t c);

  // Matrix Operations
  void operator=(Matrix<T>);
  Matrix<T> operator+(Matrix<T>);
  Matrix<T> operator-(Matrix<T>);
  Matrix<T> operator*(Matrix<T>);
  void operator+=(Matrix<T>);
  void operator-=(Matrix<T>);
  void operator*=(Matrix<T>);

  // Scalar Operations
  Matrix<T> operator+(T);
  Matrix<T> operator-(T);
  Matrix<T> operator*(T);
  Matrix<T> operator/(T);
  void operator+=(T);
  void operator-=(T);
  void operator*=(T);
  void operator/=(T);

private:
  size_t mr;
  size_t mc;
  T* mat;
  T junk = 0;
};

//----------------------------------------------------------------
// Implementation & Functions
//----------------------------------------------------------------
template<typename T>
Matrix<T>::Matrix(void) {
  mat = nullptr;
  Resize(1, 1, 0);
}

template<typename T>
Matrix<T>::Matrix(size_t r, size_t c, T val) {
  mat = nullptr;
  Resize(r, c, val);
}

template<typename T>
Matrix<T>::~Matrix(void) {
  //if (mat) delete[] mat; mat = nullptr;
}

template<typename T>
void Matrix<T>::Clear(T init_val) {
  for (unsigned int row_ind = 0; row_ind < mr; ++row_ind) {
    for (unsigned int col_ind = 0; col_ind < mc; ++col_ind) {
      this->operator()(row_ind, col_ind) = init_val;
    }
  }
}

template<typename T>
void Matrix<T>::Resize(size_t r, size_t c, T val) {
  if (r == 0) return;
  if (c == 0) return;
  mr = r;
  mc = c;
  if (mat) delete[] mat; mat = nullptr;
  mat = new T[mr * mc];
  Clear(val);
}

template<typename T>
Matrix<T> Matrix<T>::GetRow(size_t r) {
  Matrix<T> Output(1, mc, 0.0);
  for (size_t c = 0; c < mc; ++c) {
    Output(0, c) = this->operator()(r, c);
  }
  return Output;
}

template<typename T>
Matrix<T> Matrix<T>::GetCol(size_t c) {
  Matrix<T> Output(mr, 1, 0.0);
  for (size_t r = 0; r < mr; ++r) {
    Output(r, 0) = this->operator()(r,c);
  }
  return Output;
}

//----------------------------------------------------------------
// Operator Assignment
//----------------------------------------------------------------
template<typename T>
T& Matrix<T>::operator()(size_t r, size_t c) {
  if (r >= mr) return junk;
  if (c >= mc) return junk;
  return mat[r + mc * c];
}

template<typename T>
void Matrix<T>::operator=(Matrix<T> inp) {
  if (mr != inp.Rows()) return;
  if (mc != inp.Cols()) return;

  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      this->operator()(r, c) = inp(r, c);
    }
  }
}

template<typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T> inp) {
  Matrix<T> Output(mr, mc, 0.0);
  if (mr != inp.Rows()) return Output;
  if (mc != inp.Cols()) return Output;

  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      Output(r, c) = this->operator()(r, c) + inp(r, c);
    }
  }
  return Output;
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
  if (mr != inp.Rows()) return;
  if (mc != inp.Cols()) return;

  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      this->operator()(r, c) += inp(r, c);
    }
  }
}

template<typename T>
void Matrix<T>::operator+=(T scalar) {
  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      this->operator()(r, c) += scalar;
    }
  }
}

template<typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T> inp) {
  Matrix<T> Output(mr, mc, 0.0);
  if (mr != inp.Rows()) return Output;
  if (mc != inp.Cols()) return Output;

  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      Output(r, c) = this->operator()(r, c) - inp(r, c);
    }
  }
  return Output;
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
  if (mr != inp.Rows()) return;
  if (mc != inp.Cols()) return;

  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      this->operator()(r, c) -= inp(r, c);
    }
  }
}

template<typename T>
void Matrix<T>::operator-=(T scalar) {
  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      this->operator()(r, c) -= scalar;
    }
  }
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
  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      this->operator()(r, c) *= scalar;
    }
  }
}

template<typename T>
void Matrix<T>::operator/=(T scalar) {
  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      this->operator()(r, c) /= scalar;
    }
  }
}

template<typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T> inp) {
  Matrix<T> Output(mr, inp.Cols(), 0.0);
  if (mc != inp.Rows()) return Output;
  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < inp.Cols(); ++c) {
      T sum = 0;
      for (size_t x = 0; x < mr; ++x) sum += GetRow(r)(0, x) * inp.GetCol(c)(x, 0);
      Output(r, c) = sum;
    }
  }
  return Output;
}

template<typename T>
void Matrix<T>::operator*=(Matrix<T> inp) {
  if (mc != inp.Rows()) return;
  Matrix<T> out(this->operator*(inp));
  Resize(out.Rows(), out.Cols());
  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      this->operator()(r, c) = out(r, c);
    }
  }
}

template<typename T>
Matrix<T> Matrix<T>::SubMatrix(size_t r, size_t c) {
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

template<typename T>
Matrix<T> Matrix<T>::forEach(double(*func)(double)) {
  Matrix<T> output(mr, mc, 0.0);
  for (size_t r = 0; r < mr; ++r) {
    for (size_t c = 0; c < mc; ++c) {
      output(r, c) = func(this->operator()(r, c));
    }
  }
  return output;
}

//----------------------------------------------------------------
// Common Typedefs
//----------------------------------------------------------------
typedef Matrix<double> dMatrix;
typedef Matrix<int>    iMatrix;
typedef Matrix<float>  fMatrix;

#endif // MATRIX_H
