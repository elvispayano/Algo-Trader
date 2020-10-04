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

// Interface Includes
#include "interfaces/broker_controller.h"
#include "interfaces/database_controller.h"

// Neural Network Includes
#include "neuralnetwork/network_controller.h"

TraderController::TraderController( void ) {
  pBrokerCntrl   = 0;
  pDatabaseCntrl = 0;
  pNetworkCntrl  = 0;

  initialize();
}

TraderController::~TraderController( void ) {
  if ( pBrokerCntrl )
    delete pBrokerCntrl;

  if ( pDatabaseCntrl )
    delete pDatabaseCntrl;

  if ( pNetworkCntrl )
    delete pNetworkCntrl;
}

void TraderController::initialize( void ) {
  pBrokerCntrl   = new BrokerController();
}

void TraderController::perform( void ) {
  if ( pBrokerCntrl )
    pBrokerCntrl->perform();

  if ( pDatabaseCntrl )
    pDatabaseCntrl->perform();
  
  if ( pNetworkCntrl )
    pNetworkCntrl->perform();
}
