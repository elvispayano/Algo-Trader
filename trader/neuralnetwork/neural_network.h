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
#include "matrix.h"
#include "network_types.h"

// Forward Declaration
class LayerBase;

class NeuralNetwork {
public:
  // Constructor
  NeuralNetwork( std::string ticker );

  // Destructor
  ~NeuralNetwork( void );

  // Layer Configuration
  void         addLayer( LayerConfiguration configuration );
  size_t       getLayerCount( void ) { return layerList.size(); }
  unsigned int getTotalNodes( void );

  // Network Identification
  virtual std::string getTicker( void ) { return ticker; }

  // Process Network Inputs
  virtual dMatrix process( dMatrix data );

  //! @fn     train(void)
  //! @brief  Train the neural network with the provided parameters
  void train( void );

private:
  // Layer Elements
  std::vector<LayerBase*> layerList;
  std::string             ticker;
};

#endif /* NEURAL_NETWORK_H */
