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
#include <time.h>

RandomNumber::RandomNumber( void ) {
  srand( time( NULL ) );
}

RandomNumber::RandomNumber( unsigned int SEED ) {
  srand( SEED );
}

RandomNumber::~RandomNumber( void ) {}

ActivationTypes RandomNumber::activation( void ) {
  const int max = static_cast<int>( ActivationTypes::UNKNOWN );
  return static_cast<ActivationTypes>( rand() % max );
}

double RandomNumber::random( double a, double b ) {
  return ( (double)rand() / RAND_MAX ) * ( b - a ) + a;
}
