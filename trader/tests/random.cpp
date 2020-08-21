#include "random.h"
#include <stdlib.h>

double random( void ) {
  return ( double )rand() * RAND_MAX / 2 - RAND_MAX;
}

double random_p( void ) {
  return ( double )rand() * RAND_MAX;
}

double random_n( void ) {
  return -( double )rand() * RAND_MAX;
}
