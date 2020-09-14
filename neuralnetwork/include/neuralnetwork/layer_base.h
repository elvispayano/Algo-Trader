//! Layer Base
//!
//! The base layer implementation that will be the model which will
//! define the main functionality that must be present in order to
//! function with the neural network controller
//!
//! \author   Elvis Payano
//! \date     29/08/2020
//! \version  0.0.1

#ifndef LAYER_BASE_H
#define LAYER_BASE_H

// Utilities Inclues
#include "utilities/matrix.h"
#include "utilities/network_types.h"

// Forward Declaration
class Activation;

class LayerBase {
public:
  //! @fn     LayerBase( void )
  //! @brief  An empty constructor that creates the layer with a predefine
  //!         (Linear) activation type. If activation type is not set at
  //!         initialization it can be set later using the setTF function.
  LayerBase( void );

  //! @fn     LayerBase( ActivationTypes )
  //! @param  selectTF    ActivationTypes to be utilized in the layer
  //! @brief  Create the layer with the provided activation type. selectTF
  //!         can be reset at anytime using the setTF function.
  LayerBase( ActivationTypes selectTF );

  //! @fn     ~LayerBase( void )
  //! @brief  Clear any memory allocated in this layer.
  ~LayerBase( void );

  //! @fn     dMatrix process( dMatrix input)
  //!         Perform the forward propagation functionality through the layer
  //!         and generate an output that can be fed to the preceding layer.
  virtual dMatrix process( dMatrix input ) = 0;

  //! @fn     void train( double learnRate, dMatrix gradient)
  //! @param  learnRate   Measurement of how much to adjust hyperparameters in
  //!                     response to gradient
  //! @param  gradient    Description of how to modify hyperparameters in
  //!                     response to training error
  //! @brief  Run the training algorithm on this layer using the backpropagation
  //!         gradient calculated from all preceding layers.
  virtual void train( double learnRate, dMatrix gradient ) = 0;

  //! @fn     void reconfigure( size_t numNodes,
  //!                           size_t numInputs,
  //!                           dMatrix weight,
  //!                           dMatrix bias )
  //! @param  numNodes    Number of nodes present in the layer
  //! @param  numInputs   Number of inputs that will be provided to the layer
  //! @param  hyperparams Matrix containing all hyperparameters
  //! @brief  Update the layer with the provided hyperparameters that define the
  //!         required parameters for the layer
  virtual void
  reconfigure( size_t numNodes, size_t numInputs, dMatrix hyperparams );

  //! @fn     size_t getInputCount( void )
  //! @brief  Return the layers configured input size
  size_t getInputCount( void ) { return inputCount; }

  //! @fn     size_t getNodeCount( void )
  //! @brief  Return the layers configured node size
  size_t getNodeCount( void ) { return nodeCount; }

  //! @fn     dMatrix getHyperparams( void )
  //! @brief  Return the layers hyperparameters
  dMatrix getHyperparams( void ) { return hyperparameters; }

protected:
  Activation* pActivation;

  size_t inputCount;
  size_t nodeCount;

  dMatrix hyperparameters;
};

#endif /* LAYER_BASE_H */
