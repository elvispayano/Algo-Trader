//! Fully Connected Layer
//!
//! A layer type in which each node is connected to the previous and
//! next layer. The effects of the output are based on the configured
//! weights and biases.
//!
//! \author   Elvis Payano
//! \date     29/08/2020
//! \version  0.0.1

#ifndef FULLY_CONNECTED_LAYER_H
#define FULLY_CONNECTED_LAYER_H

// Neural Network Includes
#include "layer_base.h"

// Utilities Includes
#include "matrix.h"
#include "network_types.h"

class FullyConnectedLayer : public LayerBase {
public:

  //! @fn     FullyConnectedLayer( void )
  //! @brief  An empty constructor that creates the layer with a predefined (Linear)
  //!         activation type. If activation type is not set at initialization it can
  //!         be set later using the setTF function.
  FullyConnectedLayer( void );

  //! @fn     FullyConnectedLayer( ActivationTypes )
  //! @param  selectTF    ActivationTypes to be utilized in the layer
  //! @brief  Create the layer with the provided activation type. selectTF can
  //!         be reset at anytime using the setTF function.
  FullyConnectedLayer( ActivationTypes selectTF);

  //! @fn     ~FullyConnectedLayer( void )
  //! @brief  Clear any memory allocated in this layer.
  ~FullyConnectedLayer( void );

  //! @fn     dMatrix process( dMatrix input)
  //!         Perform the forward propagation functionality through the layer and
  //!         generate an output that can be fed to the preceding layer. Applying the
  //!         following function:
  //!           f(x) =  tf([weight]*[input] + bias)
  //!         where f(x) is a matrix and tf is the configured transfer function.
  dMatrix process( dMatrix input ) override;

  //! @fn     void train( double learnRate, dMatrix gradient)
  //! @param  learnRate   Measurement of how much to adjust hyperparameters in response to gradient
  //! @param  gradient    Description of how to modify hyperparameters in response to training error
  //! @brief  Run the training algorithm on this layer using the backpropagation
  //!         gradient calculated from all preceding layers. Applying the following
  //!         function:
  //!           weight = weight - learnRate * gradient
  void train( double learnRate, dMatrix gradient ) override;

  //! @fn     dMatrix getIntermediateRate( void )
  //! @brief  The derivative of the function applied by the layer in its calculation
  dMatrix getIntermediateRate( void ) { return dIntdIn; }

  //! @fn     dMatrix getOutputRate( void )
  //! @brief  The derivative of the transfer function applied on the output of the layer
  dMatrix getOutputRate( void ) { return dOutdInt; }

private:
  dMatrix dIntdIn;
  dMatrix dOutdInt;
};

#endif /* FULLY_CONNECTED_LAYER_H */
