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
  Function:   random_u
  Input:      None (void)
  Output:     (double)
  Description:
    Generate a random positive or negative number
*/
double random_u( void ) {
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

ActivationTypes random_activation( void ) {
  const int max = static_cast<int>( ActivationTypes::UNKNOWN );
  return static_cast<ActivationTypes>( rand() * max );
}

#include <time.h>

RandomNumber::RandomNumber( void ) {
  srand( time( NULL ) );
}

RandomNumber::RandomNumber( unsigned int SEED ) {
  srand( SEED );
}

RandomNumber::~RandomNumber( void ) {}

double RandomNumber::Uniform(void) {
  return (double)rand() * RAND_MAX / 2 - RAND_MAX;
}

double RandomNumber::Positive(void) {
  return (double)rand() * RAND_MAX;
}

double RandomNumber::Negative( void ) {
  return -(double)rand() * RAND_MAX;
}

ActivationTypes RandomNumber::Activation(void) {
  const int max = static_cast<int>( ActivationTypes::UNKNOWN );
  return static_cast<ActivationTypes>( rand() % max );
}
