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

  //! @fn     train(void)
  //! @brief  Train the neural network with the provided parameters
  void train( void );

private:
  // Layer Elements
  std::vector<LayerBase*> layerList;
  std::string             ticker;

  unsigned int inputCount;
  unsigned int outputCount;
};

#endif /* NEURAL_NETWORK_H */
