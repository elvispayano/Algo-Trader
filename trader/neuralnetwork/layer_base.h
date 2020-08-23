/*
  Title:
    Layer Base

  Description:
    The Layer Base class is an abstract class that will be the
    model in which will define main functionality that must be
    present in order to work with the network controller.

  Author:
    Elvis Payano
*/

#ifndef LAYER_BASE_H
#define LAYER_BASE_H

// Utilities Inclues
#include "matrix.h"
#include "network_types.h"

class Activation;

class LayerBase {
public:
  // Constructors
  LayerBase( void );
  LayerBase( ActivationTypes selectTF );

  // Destructors
  ~LayerBase( void );

  // Process layer inputs
  virtual dMatrix processLayer( dMatrix input ) = 0;

  // Configure Layer
  void reconfigure( size_t nodes, size_t inputs, dMatrix weight, dMatrix bias );

  // Layer Getters
  size_t  getInputCount( void ) { return inputCount; }
  size_t  getNodeCount( void ) { return nodeCount; }
  dMatrix getWeight( void ) { return weight; }
  dMatrix getBias( void ) { return bias; }

protected:
  Activation* pActivation;

  dMatrix weight;
  dMatrix bias;

  size_t inputCount;
  size_t nodeCount;

  dMatrix output;
};

#endif /* LAYER_BASE_H */
