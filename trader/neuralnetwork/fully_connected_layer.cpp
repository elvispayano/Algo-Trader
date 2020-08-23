/*
  Title:
    Fully Connected Layer

  Description:
    A fully connected layer is a layer type in which the each node is
    interconnected, and effects the output based on the configured
    weights and biases.

  Tests:
    test_fully_connected_layer.cc

  Author:
    Elvis Payano
*/

// Neural Network Includes
#include "fully_connected_layer.h"
#include "activation.h"

/*
  Constructor:  Fully Connected Layer
  Inputs:       None (void)

  Description:
    Initialize the fully connected layer with a default activation function
*/
FullyConnectedLayer::FullyConnectedLayer( void )
    : LayerBase( ActivationTypes::LINEAR ) {}

/*
  Constructor:  Fully Connected Layer
  Inputs:       selectTF (Activation Types [enum])

  Description:
    Initialize the fully connected layer with the provided activation
    function settings
*/
FullyConnectedLayer::FullyConnectedLayer( ActivationTypes selectTF )
    : LayerBase( selectTF ) {}

/*
  Destructor:   ~Fully Connected Layer
  Inputs:       None (void)

  Description:
    Clear any dynamically allocated memory
*/
FullyConnectedLayer::~FullyConnectedLayer( void ) {}

/*
  Function:     processLayer
  Inputs:       input (dMatrix)

  Description:
    Process inputs into layer using the following function:
      f(x) =  tf([weight]*[input] + bias)
    where f(x) is a matrix and tf is the configure transfer
    function
*/
dMatrix FullyConnectedLayer::processLayer( dMatrix input ) {
  output = pActivation->performTF( weight * input + bias );
  return output;
}
