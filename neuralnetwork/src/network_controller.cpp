/// Neural Network Controller
///
/// The neural network controller interface that handles the platforms with the
/// various neural networks that are deployed
///
/// \author   Elvis Payano
/// \date     02/10/2020
/// \version  0.0.1

// Neural Network Includes
#include "neuralnetwork/network_controller.h"
#include "neuralnetwork/neural_network.h"

NetworkController::NetworkController( void ) {
  networkList.clear();
}

NetworkController::~NetworkController( void ) {
  for ( NeuralNetwork* network : networkList ) {
    delete network;
  }
  networkList.clear();
}

void NetworkController::perform( void ) {}
