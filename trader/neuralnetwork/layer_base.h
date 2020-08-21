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

// Neural Network Includes
#include "activation.h"

// Utilities Inclues
#include "matrix.h"

class LayerBase : public Activation {
public:
  // Constructors
  LayerBase( void );
  LayerBase( ActivationTypes selectTF );

  // Destructors
  ~LayerBase( void );

  // Process layer inputs
  virtual dMatrix processLayer( dMatrix input ) = 0;

  // Configure Layer
  void reconfigure( void );

  // Layer Setters
  void setInputCount( size_t count ) { inputCount = count; }
  void setNodeCount( size_t count ) { nodeCount = count; }
  void setWeight( dMatrix input ) { weight = input; }
  void setBias( dMatrix input ) { bias = input; }

  // Layer Getters
  size_t  getInputCount( void ) { return inputCount; }
  size_t  getNodeCount( void ) { return nodeCount; }
  dMatrix getWeight( void ) { return weight; }
  dMatrix getBias( void ) { return bias; }

protected:
  dMatrix weight;
  dMatrix bias;

  size_t inputCount;
  size_t nodeCount;
};

#endif /* LAYER_BASE_H */
