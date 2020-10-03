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
  pBroker   = 0;
  pDatabase = 0;
  pNetwork  = 0;
}

TraderController::~TraderController( void ) {
  if ( pBroker )
    delete pBroker;

  if ( pDatabase )
    delete pDatabase;

  if ( pNetwork )
    delete pNetwork;
}

void TraderController::initialize( void ) {
  pBroker   = new BrokerController();
  pDatabase = new DatabaseController();
  pNetwork  = new NetworkController();
}

void TraderController::perform( void ) {
  if ( pBroker )
    pBroker->perform();

  if ( pDatabase )
    pDatabase->perform();

  if ( pNetwork )
    pNetwork->perform();
}