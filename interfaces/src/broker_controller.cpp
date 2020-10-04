
// Interface Includes
#include "interfaces/broker_controller.h"
#include "ib_wrapper.h"
#include "interactive_broker.h"

enum class RequestID {
  UPDATE,
  MARKETPURCHASE,
  MARKETSELL,
  LIMITPURCHASE,
  LIMITSELL,
  STOPPURCHASE,
  STOPSELL,
  UNKNOWN
};

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
  RequestID   reqID = RequestID::UNKNOWN;

  switch ( reqID ) {
  case RequestID::UPDATE:
    pBroker->requestUpdate();
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
  pBroker->connectionManager();

  pBroker->perform();
}

void BrokerController::processOutputs( void ) {}
