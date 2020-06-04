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
  weight.Clear(0.0);
  bias.Clear(0.0);
  setTF(ActivationTypes::NONE);

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
  weight.Clear(0.0);
  bias.Clear(0.0);
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

void LayerBase::reconfigure(void) {
  weight.Resize(nodeCount, inputCount, 0.0);
  bias.Resize(inputCount, 1, 0.0);
}