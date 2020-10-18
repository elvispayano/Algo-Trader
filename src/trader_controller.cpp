/// Trader Controller
///
/// The logic that controls the sequencing order in which the trader platform
/// will operate
///
/// \author   Elvis Payano
/// \date     02/10/2020
/// \version  0.0.1

// Algo Trader Includes
#include "trader_controller.h"
#include "broker_controller.h"
#include "database_controller.h"
#include "network_controller.h"

TraderController::TraderController( void ) {
  // Controllers
  pBrokerCntrl   = 0;
  pDatabaseCntrl = 0;
  pNetworkCntrl  = 0;

  // FIFOs
  pPortBroker = 0;

  pServer = 0;

  initialize();
}

TraderController::~TraderController( void ) {
  if ( pBrokerCntrl )
    delete pBrokerCntrl;

  if ( pDatabaseCntrl )
    delete pDatabaseCntrl;

  if ( pNetworkCntrl )
    delete pNetworkCntrl;

  if ( pServer )
    delete pServer;
}

void TraderController::initialize( void ) {
  pServer = new DataServer();

  // Create Controllers
  pBrokerCntrl   = new BrokerController();
  pNetworkCntrl  = new NetworkController( pServer );
  pDatabaseCntrl = new DatabaseController( pServer );

  // Initialize Ports
  pPortBroker = new FIFOBidirectional<BrokerResponseMsg, BrokerRequestMsg>;
  pPortDatabase =
      new FIFOBidirectional<DatabaseResponseMsg, DatabaseRequestMsg>;

  // Broker Port Installation
  pBrokerCntrl->install( pPortBroker );

  // Neural Network Port Installation
  pNetworkCntrl->install( pPortBroker );
  pNetworkCntrl->install( pPortDatabase );

  // Database Port Installation
  pDatabaseCntrl->install( pPortDatabase );
}

void TraderController::perform( void ) {
  if ( pBrokerCntrl )
    pBrokerCntrl->perform();

  if ( pDatabaseCntrl )
    pDatabaseCntrl->perform();

  if ( pNetworkCntrl )
    pNetworkCntrl->perform();
}
