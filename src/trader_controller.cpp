/// Trader Controller
///
/// The logic that controls the sequencing order in which the trader platform
/// will operate
///
/// \author   Elvis Payano
/// \date     02/10/2020
/// \version  0.0.1

// Algo Trader Includes
#include "algo-trader/trader_controller.h"

// Neural Network Includes
#include "neuralnetwork/network_controller.h"

TraderController::TraderController( void ) {
  pNetwork = 0;
}

TraderController::~TraderController( void ) {
  if ( pNetwork ) {
    delete pNetwork;
  }
}

void TraderController::initialize(void) {
  pNetwork = new NetworkController();
}

void TraderController::perform( void ) {
  pNetwork->perform();
}
