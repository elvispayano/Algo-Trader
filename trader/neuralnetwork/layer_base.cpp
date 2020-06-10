/*
  Title:
    Activation

  Description:
    This Activation class is responsible for processing the
    layers output through a desired transfer function. This
    class contains a subset of the functionality that is
    required for the data flow through any given layer.

  Author:
    Elvis Payano
*/

// Neural Network Includes
#include "layer_base.h"

/*
  Constructor:  Layer Base
  Inputs:       None (void)

  Description:
    Initialize the weights and bias with zeros and
    default activation function (None)
*/
LayerBase::LayerBase(void) {
  weight.clear(0.0);
  bias.clear(0.0);
  setTF(ActivationTypes::LINEAR);

  inputCount = 0;
  nodeCount  = 0;
}

/*
  Constructor:  Layer Base
  Inputs:       selectTF (Activation Types)

  Description:
    Initialize the weights and bias with zeros and
    the selected activation function
*/
LayerBase::LayerBase(ActivationTypes selectTF) {
  weight.clear(0.0);
  bias.clear(0.0);
  setTF(selectTF);

  inputCount = 0;
  nodeCount  = 0;
}

/*
  Destructor:   ~Layer Base
  Inputs:       None (void)

  Description:
    Clear any dynamically allocated memory
*/
LayerBase::~LayerBase(void) {

}

/*
  Function:     reconfigure
  Inputs:       None (void)

  Description:
    Use the configured settings of nodeCount & inputCount
    to set the appropriate size for the layer weights and
    biases.
*/
void LayerBase::reconfigure(void) {
  weight.resize(nodeCount, inputCount, 0.0);
  bias.resize(nodeCount, 1, 0.0);
}
