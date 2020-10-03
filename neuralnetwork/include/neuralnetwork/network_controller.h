/// Neural Network Controller
///
/// The neural network controller interface that handles the platforms with the
/// various neural networks that are deployed
///
/// \author   Elvis Payano
/// \date     02/10/2020
/// \version  0.0.1

#ifndef NETWORK_CONTROLLER_H
#define NETWORK_CONTROLLER_H

// Neural Network Includes
#include "neural_network.h"

// Standard Includes
#include <vector>

// Forward Declaration
class NeuralNetwork;

class NetworkController {
public:
  NetworkController( void );
  ~NetworkController( void );

  void perform( void );

private:
  std::vector<NeuralNetwork*> networkList;
};

#endif /* NETWORK_CONTROLLER_H */
