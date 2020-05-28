#ifndef MATRIX_H
#define MATRIX_H

template<typename T>
class Matrix {
public:
  // Implementation & Functions
  Matrix(void);
  Matrix(size_t r, size_t c, T = 0.0);

  void Clear(T = 0.0);
  void Resize(size_t r, size_t c);
  size_t Rows(void) { return mr; }
  size_t Cols(void) { return mc; }

  // Operators
  T& operator()(int, int);
  Matrix<T> operator+(Matrix<T>);
  Matrix<T> operator-(Matrix<T>);
  void operator+=(Matrix<T>);
  void operator-=(Matrix<T>);

private:
  size_t mr;
  size_t mc;
  T* mat;
};

//----------------------------------------------------------------
// Implementation & Functions
//----------------------------------------------------------------
template<typename T>
Matrix<T>::Matrix(void) {
  mr = 0;
  mc = 0;
  mat = 0;
  Resize(mr, mc);
  Clear(static_cast<T>(0));
}

template<typename T>
Matrix<T>::Matrix(size_t r, size_t c, T init_val) {
  mr = r;
  mc = c;
  mat = 0;
  Resize(mr, mc);
  Clear(static_cast<T>(init_val));
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
void Matrix<T>::Resize(size_t r, size_t c) {
  mr = r;
  mc = c;
  if (mat) delete mat; mat = 0;
  mat = new T[mr * mc];
  Clear(0.0);
}

//----------------------------------------------------------------
// Operator Assignment
//----------------------------------------------------------------
template<typename T>
T& Matrix<T>::operator()(int r, int c) {
  T output = 0;
  if ((mr > r) && (mc > c)) {
    return mat[r + mc * c];
  }
  return output;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T> inp) {
  Matrix<T> Output(Rows(), Cols());
  if (Rows() != inp.Rows() || Cols() != Cols()) {
    return Output;
  }
  else {
    for (unsigned int row_ind = 0; row_ind < Rows(); ++row_ind) {
      for (unsigned int col_ind = 0; col_ind < Cols(); ++col_ind) {
        Output(row_ind, col_ind) = this->operator()(row_ind, col_ind) + inp(row_ind, col_ind);
      }
    }
  }
  return Output;
}

template<typename T>
void Matrix<T>::operator+=(Matrix<T> inp) {
  if (Rows() == inp.Rows() || Cols() == Cols()) {
    for (unsigned int row_ind = 0; row_ind < Rows(); ++row_ind) {
      for (unsigned int col_ind = 0; col_ind < Cols(); ++col_ind) {
        this->operator()(row_ind, col_ind) += inp(row_ind, col_ind);
      }
    }
  }
}

template<typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T> inp) {
  Matrix<T> Output(Rows(), Cols());
  if (Rows() != inp.Rows() || Cols() != Cols()) {
    return Output;
  }
  else {
    for (unsigned int row_ind = 0; row_ind < Rows(); ++row_ind) {
      for (unsigned int col_ind = 0; col_ind < Cols(); ++col_ind) {
        Output(row_ind, col_ind) = this->operator()(row_ind, col_ind) - inp(row_ind, col_ind);
      }
    }
  }
  return Output;
}

template<typename T>
void Matrix<T>::operator-=(Matrix<T> inp) {
  if (Rows() == inp.Rows() || Cols() == Cols()) {
    for (unsigned int row_ind = 0; row_ind < Rows(); ++row_ind) {
      for (unsigned int col_ind = 0; col_ind < Cols(); ++col_ind) {
        this->operator()(row_ind, col_ind) -= inp(row_ind, col_ind);
      }
    }
  }
}

//----------------------------------------------------------------
// Common Typedefs
//----------------------------------------------------------------
typedef Matrix<double> dMatrix;
typedef Matrix<int>    iMatrix;
typedef Matrix<float>  fMatrix;

#endif // MATRIX_H