//! Layer Base
//!
//! The base layer implementation that will be the model which will
//! define the main functionality that must be present in order to
//! function with the neural network controller
//!
//! \author   Elvis Payano
//! \date     29/08/2020
//! \version  0.0.1

// Neural Network Includes
#include "neuralnetwork/layer_base.h"
#include "neuralnetwork/activation.h"

//! @fn     LayerBase( void )
//! @brief  An empty constructor that creates the layer with a predefine
//!         (Linear) activation type. If activation type is not set at
//!         initialization it can be set later using the setTF function.
LayerBase::LayerBase( void )
    : pActivation( new Activation() ) {
  inputCount = 0;
  nodeCount  = 0;
}

//! @fn     LayerBase( ActivationTypes )
//! @param  selectTF    ActivationTypes to be utilized in the layer
//! @brief  Create the layer with the provided activation type. selectTF
//!         can be reset at anytime using the setTF function.
LayerBase::LayerBase( ActivationTypes selectTF )
    : pActivation( new Activation( selectTF ) ) {
  inputCount = 0;
  nodeCount  = 0;
}

//! @fn     ~LayerBase( void )
//! @brief  Clear any memory allocated in this layer.
LayerBase::~LayerBase( void ) {
  if ( pActivation )
    delete pActivation;
}

//! @fn     void reconfigure( size_t numNodes,
//!                           size_t numInputs,
//!                           dMatrix weight,
//!                           dMatrix bias )
//! @param  numNodes    Number of nodes present in the layer
//! @param  numInputs   Number of inputs that will be provided to the layer
//! @param  hyperparams Matrix containing all hyperparameters
//! @brief  Update the layer with the provided hyperparameters that define the
//!         required parameters for the layer
void LayerBase::reconfigure(size_t nodes, size_t inputs, dMatrix hyperparams) {
  inputCount = inputs;
  nodeCount  = nodes;
}
