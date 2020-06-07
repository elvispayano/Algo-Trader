
// Utility Includes
#include "utl_math.h"

// C++ Standard Includes
#include <cmath>

/*
  Function:     sig
  Inputs:       (primitive type)
  Output:       (primitive type)

  Description:
    Process input through Sigmoid transfer function.

  Transfer Function Equation:
    f(x) = 1/(1+e^(-x))
*/
template<typename T>
T sigmoid(T x) {
  return 1 / (1 + exp(-x));
}

/*
  Function:     htan
  Inputs:       (primitive type)
  Output:       (primitive type)

  Description:
    Process input through Hyperbolic Tangent transfer
    function.

  Transfer Function Equation:
    f(x) = (e^x - e^(-x))/(e^x + e^(-x))
*/
template<typename T>
T htan(T x) {
  return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
}

/*
  Function:     binary
  Inputs:       (primitive type)
  Output:       (primitive type)

  Description:
    Process input through Binary transfer function.

  Transfer Function Equation:
    f(x) = 1   | x >= 0
    f(x) = 0   | x <  0
*/
template<typename T>
T binary(T x) {
  if (x >= 0) return 1;
  return 0;
}

/*
  Function:     relu
  Inputs:       (primitive type)
  Output:       (primitive type)

  Description:
    Process input through Recitified Linear Unit
    transfer function.

  Transfer Function Equation:
    f(x) = x   | x >  0
    f(x) = 0   | x <= 0
*/
template<typename T>
T relu(T x) {
  if (x > 0) return x;
  return 0;
}

/*
  Function:     lin
  Inputs:       (primitive type)
  Output:       (primitive type)

  Description:
    No processing of inputs through a transfer
    function.

  Transfer Function Equation:
    f(x) = f(x)
*/
template<typename T>
T linear(T x) {
  return x;
}