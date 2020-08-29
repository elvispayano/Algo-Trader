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

// Neural Network Includes
#include "layer_base.h"
#include "activation.h"

/*
  Constructor:  Layer Base
  Inputs:       None (void)

  Description:
    Initialize the weights and bias with zeros and
    default activation function (None)
*/
LayerBase::LayerBase( void )
    : pActivation( new Activation() ) {

  weight.clear( 0.0 );
  bias.clear( 0.0 );

  inputCount = 0;
  nodeCount  = 0;

  outputs.clear( 0.0 );
  intermediate.clear( 0.0 );
  inputs.clear( 0.0 );
}

/*
  Constructor:  Layer Base
  Inputs:       selectTF (Activation Types)

  Description:
    Initialize the weights and bias with zeros and
    the selected activation function
*/
LayerBase::LayerBase( ActivationTypes selectTF )
    : pActivation( new Activation( selectTF ) ) {

  weight.clear( 0.0 );
  bias.clear( 0.0 );

  inputCount = 0;
  nodeCount  = 0;

  outputs.clear( 0.0 );
  intermediate.clear( 0.0 );
  inputs.clear( 0.0 );
}

/*
  Destructor:   ~Layer Base
  Inputs:       None (void)

  Description:
    Clear any dynamically allocated memory
*/
LayerBase::~LayerBase( void ) {
  if ( pActivation )
    delete pActivation;
}

/*
  Function:     reconfigure
  Inputs:       numNodes (size_t), numInputs (size_t)
                weight (dMatrix), bias (dMatrix)

  Description:
    Use the configured settings of nodeCount & inputCount
    to set the appropriate size for the layer weights and
    biases.
*/
void LayerBase::reconfigure( size_t  numNodes,
                             size_t  numInputs,
                             dMatrix weight,
                             dMatrix bias ) {
  this->weight.resize( numNodes, numInputs, 0.0 );
  this->weight = weight;

  this->bias.resize( numNodes, 1, 0.0 );
  this->bias = bias;

  nodeCount  = numNodes;
  inputCount = numInputs;

  outputs.resize( numNodes, 1, 0.0 );
  intermediate.resize( numInputs, 1, 0.0 );
  inputs.resize( numInputs, 1, 0.0 );
}
