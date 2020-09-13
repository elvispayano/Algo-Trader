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
  ActivationTypes activation( void );
  double          random( double a = 0.0, double b = 100.0);

  //! @fn     layerConfig( void )
  //! @brief  Generate a random layer configuration
  LayerConfiguration layerConfig( void );

  //! @fn     layer( void )
  //! @brief  Generate a random layer type
  LayerTypes layer( void );
};
