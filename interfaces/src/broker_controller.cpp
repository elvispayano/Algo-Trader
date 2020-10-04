
// Comms Includes
#include "comms/broker_request_msg.h"
#include "comms/broker_request_update_msg.h"
#include "comms/broker_response_msg.h"
#include "comms/broker_response_update_msg.h"

// Interface Includes
#include "interfaces/broker_controller.h"
#include "ib_wrapper.h"
#include "interactive_broker.h"

BrokerController::BrokerController( void ) {
  pBroker = 0;

  initialize();
}

BrokerController::~BrokerController( void ) {}

void BrokerController::initialize( void ) {
  pBroker = new InteractiveBroker( new IBWrapper( "127.0.0.1", 6550, 0 ) );
}

void BrokerController::perform( void ) {
  processInputs();

  update();

  processOutputs();
}

/// @fn     void processInputs
/// @brief  Process messages from the trader platform to the broker API
void BrokerController::processInputs( void ) {
  if ( !pBroker->isConnected() )
    return;

  RequestID reqID = bReqMsg->getID();

  switch ( reqID ) {
  case RequestID::UPDATE:
    if ( bReqUpdateMsg->decode( bReqMsg ) ) {
      pBroker->requestUpdate( bReqUpdateMsg );
    }
    break;

  case RequestID::MARKETPURCHASE:
    pBroker->requestMarketPurchase();
    break;

  case RequestID::MARKETSELL:
    pBroker->requestMarketSell();
    break;

  case RequestID::LIMITPURCHASE:
    pBroker->requestLimitPurchase();
    break;

  case RequestID::LIMITSELL:
    pBroker->requestLimitSell();
    break;

  case RequestID::STOPPURCHASE:
    pBroker->requestStopPurchase();
    break;

  case RequestID::STOPSELL:
    pBroker->requestStopSell();
    break;
  }
}

void BrokerController::update( void ) {
  // Check Connection Status
  pBroker->connect();

  pBroker->perform();
}

void BrokerController::processOutputs( void ) {}
