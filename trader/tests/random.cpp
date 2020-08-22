/*
  Title:
    Random

  Description:
    Implementation of random number generators to be used in tests

  Author:
    Elvis Payano
*/

// Test Includes
#include "random.h"

// Standard Includes
#include <stdlib.h>

/*
  Function:   random
  Input:      None (void)
  Output:     (double)
  Description:
    Generate a random positive or negative number
*/
double random( void ) {
  return (double)rand() * RAND_MAX / 2 - RAND_MAX;
}

/*
  Function:   random_p
  Input:      None (void)
  Output:     (double)
  Description:
    Generate a random positive number
*/
double random_p( void ) {
  return (double)rand() * RAND_MAX;
}

/*
  Function:   random_n
  Input:      None (void)
  Output:     (double)
  Description:
    Generate a random negative number
*/
double random_n( void ) {
  return -(double)rand() * RAND_MAX;
}
