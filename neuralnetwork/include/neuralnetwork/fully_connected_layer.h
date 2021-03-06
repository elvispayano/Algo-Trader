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
#include "neuralnetwork/layer_base.h"

// Utilities Includes
#include "utilities/matrix.h"
#include "utilities/network_types.h"

class FullyConnectedLayer : public LayerBase {
public:
  //! @fn     FullyConnectedLayer( void )
  //! @brief  An empty constructor that creates the layer with a predefined
  //!         (Linear) activation type. If activation type is not set at
  //!         initialization it can be set later using the setTF function.
  FullyConnectedLayer( void );

  //! @fn     FullyConnectedLayer( ActivationTypes )
  //! @param  selectTF    ActivationTypes to be utilized in the layer
  //! @brief  Create the layer with the provided activation type. selectTF can
  //!         be reset at anytime using the setTF function.
  FullyConnectedLayer( ActivationTypes selectTF );

  /// @fn     FullConnectedLayer( ActivationTypes activation, unsigned int
  ///                             inputs, unsigned int nodes )
  /// @param  activation
  /// @param  inputs
  /// @param  nodes
  /// @brief  Create the layer with the provided activation type, and configure
  /// the weight and biases appropriate for the expected inputs and nodes.
  FullyConnectedLayer( ActivationTypes activation,
                       unsigned int    inputs,
                       unsigned int    nodes );

  //! @fn     ~FullyConnectedLayer( void )
  //! @brief  Clear any memory allocated in this layer.
  ~FullyConnectedLayer( void );

  //! @fn     void reconfigure( size_t nodes,
  //!                           size_t inputs,
  //!                           Matrix hyperparams )
  //! @param  nodes       Number of nodes present in layer
  //! @param  inputs      Number of inputs present in layer
  //! @param  hyperparam  Matrix of hyperparameters containing all weight and
  //!                     bias values
  //! @brief  Update the layer with the provided hyperparameters that define the
  //!         required configuration of the layer
  void reconfigure( size_t nodes, size_t inputs, Matrix hyperparams ) override;

  //! @fn     Matrix process( Matrix input)
  //!         Perform the forward propagation functionality through the layer
  //!         and generate an output that can be fed to the preceding layer.
  //!         Applying the following function:
  //!           f(x) =  tf([weight]*[input] + bias)
  //!         where f(x) is a matrix and tf is the configured transfer function.
  Matrix process( Matrix input ) override;

  //! @fn     void train( double learnRate, Matrix gradient)
  //! @param  learnRate   Measurement of how much to adjust hyperparameters in
  //!                     response to gradient
  //! @param  gradient    Description of how to modify hyperparameters in
  //!                     response to training error
  //! @brief  Run the training algorithm on this layer using the backpropagation
  //!         gradient calculated from all preceding layers. Applying the
  //!         following function:
  //!           weight = weight - learnRate * gradient
  void train( double learnRate, Matrix gradient ) override;

  //! @fn     Matrix getIntermediateRate( void )
  //! @brief  The derivative of the function applied by the layer in its
  //!         calculation
  Matrix getIntermediateRate( void ) { return dIntdIn; }

  //! @fn     Matrix getOutputRate( void )
  //! @brief  The derivative of the transfer function applied on the output of
  //!         the layer
  Matrix getOutputRate( void ) { return dOutdInt; }

  //! @fn     Matrix getWeight( void )
  //! @brief  Return the layers configured weight hyperparameters
  Matrix getWeight( void ) { return weight; }

  //! @fn     Matrix getBias( void )
  //! @brief  Return the layers configured bias hyperparameters
  Matrix getBias( void ) { return bias; }

  /// @fn     void configure( unsigned int index, float value )
  /// @param  index
  /// @param  value
  /// @brief  Apply hyperparameters to layer
  void configure( unsigned int index, float value );

private:
  // Hyperparameters
  Matrix weight;
  Matrix bias;

  Matrix dIntdIn;
  Matrix dOutdInt;

  Matrix inputs;
  Matrix outputs;
  Matrix intermediate;

  Matrix updateRate;
  Matrix outputRate;
};

#endif /* FULLY_CONNECTED_LAYER_H */
