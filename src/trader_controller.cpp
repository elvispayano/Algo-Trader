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
  // Controllers
  pBrokerCntrl   = 0;
  pDatabaseCntrl = 0;
  pNetworkCntrl  = 0;

  // FIFOs
  pPortBroker = 0;

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
  // Create Controllers
  pBrokerCntrl   = new BrokerController();
  pNetworkCntrl  = new NetworkController();
  pDatabaseCntrl = new DatabaseController();

  // Initialize Ports
  pPortBroker = new FIFOBidirectional<BrokerResponseMsg, BrokerRequestMsg>;

  // Port Installation
  pBrokerCntrl->install( pPortBroker );
  pNetworkCntrl->install( pPortBroker );
}

void TraderController::perform( void ) {
  if ( pBrokerCntrl )
    pBrokerCntrl->perform();

  if ( pDatabaseCntrl )
    pDatabaseCntrl->perform();

  if ( pNetworkCntrl )
    pNetworkCntrl->perform();
}
