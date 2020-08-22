/*
  Title:
    Random

  Description:
    Implementation of random number generators to be used in tests

  Author:
    Elvis Payano
*/

// Utility Includes
#include "network_types.h"

class RandomNumber {
public:
  RandomNumber( void );
  RandomNumber( unsigned int SEED);
  ~RandomNumber( void );

  double Uniform( void );
  double Positive( void );
  double Negative( void );
  static ActivationTypes Activation( void );
};

double random_u( void );
double random_p( void );
double random_n( void );

ActivationTypes random_activation( void );
