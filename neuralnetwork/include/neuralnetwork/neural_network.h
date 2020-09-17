//! Neural Network
//!
//! This class is responsible for generating and configuring all the neural
//! network layers. This class is also the main interface for the outside
//! implementation.
//!
//! \author   Elvis Payano
//! \date     04/09/2020
//! \version  0.0.1

#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

// Standard Includes
#include <string>
#include <vector>

// Utility Includes
#include "utilities/matrix.h"
#include "utilities/network_types.h"

// Forward Declaration
class LayerBase;

class NeuralNetwork {
public:
  //! @fn     NeuralNetwork( void )
  //! @brief  Initialize a neural network and layer workspace that will later be
  //!         configured.
  NeuralNetwork( void );

  //! @fn     NeuralNetwork( string name )
  //! @brief  Initialize a neural network and layer workspace that will later be
  //!         configured.
  NeuralNetwork( std::string name );

  //! @fn     ~NeuralNetwork( string ticker )
  //! @brief  The neural network is composed of various layer pointers that are
  //!         created. Upon destruction of the class, the created pointers must
  //!         be deleted.
  ~NeuralNetwork( void );

  //! @fn     void addLayer( LayerConfiguration configuration )
  //! @brief  Add a new layer to the network. The configuration type contains
  //!         all the required elements to select the type of layer, implemented
  //!         activation, and the size of the layer.
  void addLayer( LayerConfiguration configuration );

  //! @fn     unsigned int getLayerCount( void )
  //! @brief  Total layers used within the network.
  size_t getLayerCount( void ) { return layerList.size(); }

  //! @fn     unsigned int getHiddenLayerCount( void )
  //! @brief  Total hidden layers present within the network
  unsigned int getHiddenLayerCount( void ) { return layerList.size(); }

  //! @fn     unsigned int getTotalNodes( void )
  //! @brief  Total nodes used within the network. It is used to determine
  //!         approximate complexity.
  unsigned int getTotalNodes( void );

  // Network Identification
  virtual std::string getTicker( void ) { return ticker; }

  //! @fn     dMatrix process( dMatrix data )
  //! @brief  Process input data through each layer and return a proccessed
  //!         matrix containing the desired action to be performed.
  virtual dMatrix process( dMatrix data );

  //! @fn     train( void )
  //! @brief  Train the neural network with the provided parameters
  void train( void );

  //! @fn     getLayer( unsigned int index )
  //! @brief  Return the desired layer so that it can be updated
  LayerBase* getLayer( unsigned int index ) { return layerList[index - 1]; }

  //! @fn     getInputLayer( void )
  //! @brief  Return the input layer of the network
  LayerBase* getInputLayer( void ) { return inputLayer; }

  //! @fn     getOutputLayer( void )
  //! @brief  Return the output layer of the network
  LayerBase* getOutputLayer( void ) { return outputLayer; }

  //! @fn     setInputs( unsigned int count )
  //! @brief  Set the number of inputs for the neural network
  void setInputs( unsigned int count );

  //! @fn     setOutputs( unsigned int count )
  //! @brief  Set the number of outputs for the neural network
  void setOutputs( unsigned int count );

  //! @fn     addInputLayer( unsigned int inputs, LayerConfiguration config )
  //! @param  inputs  Number of inputs the network should expect
  //! @param  config  Layer configuration parameters
  //! @brief  Configure the network input layer
  void addInputLayer( unsigned int inputs, LayerConfiguration config );

  //! @fn     addOutputLayer( unsigned int inputs, LayerConfiguration config )
  //! @param  outputs Number of outputs the network should expect
  //! @param  config  Layer configuration parameters
  //! @brief  Configure the network output layer
  void addOutputLayer( unsigned int inputs, LayerConfiguration config );

private:
  //! @fn     LayerBase* newLayer(ActivationTypes activation, LayerTypes layer)
  //! @param  activation  Defining layer activation type
  //! @param  layer       Defining type of layer to create
  //! @brief  
  LayerBase* newLayer( ActivationTypes activation, LayerTypes layer );

  // Layer Elements
  LayerBase*              inputLayer;
  LayerBase*              outputLayer;
  std::vector<LayerBase*> layerList;

  std::string ticker;

  unsigned int inputCount;
  unsigned int outputCount;
};

#endif /* NEURAL_NETWORK_H */
