#include "broker_controller.h"

// Interface Includes
#include "ib_wrapper.h"
#include "interactive_broker.h"

BrokerController::BrokerController( void ) {
  pBroker = 0;
  pPort   = 0;

  initialize();
}

BrokerController::~BrokerController( void ) {}

/// @fn     void initialize( void )
/// @brief  Initialize the broker controller with the configured settings
void BrokerController::initialize( void ) {
  pBroker = new InteractiveBroker( new IBWrapper( "127.0.0.1", 6550, 0 ) );
}

/// @fn     void perform( void )
/// @brief  Perform a broker controller update
void BrokerController::perform( void ) {
  // Check Connection Status
  if ( !pBroker->isConnected() ) {
    pBroker->connect();
    return;
  }

  pBroker->performInput();

  pBroker->performOutput();
}

/// @fn     void install( FIFOBidirectional< BrokerRequestMsg,
///                       BrokerRequestMsg >* port )
/// @param  port  Installed broker port
/// @brief  Provide the broker interface with the installed communication
///         port.
void BrokerController::install(
    FIFOBidirectional<BrokerResponseMsg, BrokerRequestMsg>* port ) {
  pPort = port;
  pBroker->install( pPort );
}
