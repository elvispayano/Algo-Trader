#ifndef MATH_H
#define MATH_H

#include "matrix.h"

dMatrix tanh(dMatrix);  // Transfer Function: Hyperbolic Tanger
dMatrix sig (dMatrix);  // Transfer Function: Sigmoid
dMatrix relu(dMatrix);  // Transfer Function: Rectified Linear Unit
dMatrix bin (dMatrix);  // Transfer Function: Binary
dMatrix lin (dMatrix);  // Transfer Function: None

#endif /* MATH_H */