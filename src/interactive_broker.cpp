/*
  Title:
    Interactive Broker

  Description:
    This class is responsbile for configuring and managing the Interactive
    Broker connection. The main objective of this call is to ensure that all
    requests are properly fulfilled

  Test:
    test_interactive_broker.cc

  Author:
    Elvis Payano
*/

// Interface Includes
#include "interactive_broker.h"
#include "ib_wrapper.h"

// Comms Includes
#include "comms/broker_request_update_msg.h"

// Standard Includes
#include <chrono>
#include <functional>

/// @fn     InteractiveBroker( IBWrapper* wrapper )
/// @param  wrapper   Interactive Broker API wrapper
/// @brief  Setup configuration for the Interactive Broker connection
InteractiveBroker::InteractiveBroker( IBWrapper* wrapper )
    : ib( wrapper ) {
  disconnectTrigger = false;
  frame50           = true;
  tProcess          = 0;

  messages.empty();

  pPort = 0;
}

/*
  Desctructor:  ~InteractiveBroker
  Inputs:       None (void)

  Description:
    Ensure Interactive Broker connection is safely terminated during object
    destruction
*/
InteractiveBroker::~InteractiveBroker( void ) {
  terminateConnection();
}

/// @fn     void install( FIFOBidirectional< BrokerRequestMsg,
///                       BrokerRequestMsg >* port )
/// @param  port  Installed broker port
/// @brief  Provide the broker interface with the installed communication
///         port.
void InteractiveBroker::install(
    FIFOBidirectional<BrokerResponseMsg, BrokerRequestMsg>* port ) {
  pPort = port;
}

/// @fn     bool isConnected( void )
/// @brief  Check if a valid connection to the broker exists
bool InteractiveBroker::isConnected( void ) {
  return ib->isConnected();
}

/// @fn     void connect( void )
/// @brief  Attempt to establish a connection to an Interactive Broker API using
///         the configured parameters
void InteractiveBroker::connect( void ) {
  if ( !isConnected() )
    ib->connect();
}

/// @fn     void performInput( void )
/// @brief  Process request messages from Interactive Broker API
void InteractiveBroker::performInput( void ) {
  BrokerRequestMsg msg;

  if ( !isConnected() || !pPort->getOutput( msg ) ) {
    return;
  }

  switch ( msg.getID() ) {
  case RequestID::UPDATE:
    if ( bReqUpdateMsg.decode( &msg ) ) {
      requestUpdate( &bReqUpdateMsg );
    }
    break;

  case RequestID::MARKETPURCHASE:
    requestMarketPurchase();
    break;

  case RequestID::MARKETSELL:
    requestMarketSell();
    break;

  case RequestID::LIMITPURCHASE:
    requestLimitPurchase();
    break;

  case RequestID::LIMITSELL:
    requestLimitSell();
    break;

  case RequestID::STOPPURCHASE:
    requestStopPurchase();
    break;

  case RequestID::STOPSELL:
    requestStopSell();
    break;

  default:
    printf( "Unknown Message Request\n" );
    break;
  }
}

/// @fn     void performInput( void )
/// @brief  Process response messages from Interactive Broker API
void InteractiveBroker::performOutput( void ) {
  if ( !isConnected() ) {
    return;
  }

  ib->processMessages();

  BrokerResponseMsg temp;
  if ( ib->getResponse( temp ) ) {
    pPort->putInput( temp );
  }
}

/// @fn     void requestUpdate(  BrokerRequestMsg& msg )
/// @param  msg   Input Message
/// @brief  Request a ticker update
void InteractiveBroker::requestUpdate( BrokerRequestUpdateMsg* msg ) {
  ib->getCurrentPrice( msg->ticker );
}

/// @fn     void connectionManager
/// @brief  Establish a new connection to the broker interface if one does not
///         exist. If a connnection does exist, do no establish a new one. Runs
///         continously to ensure a valid connection is always available.
void InteractiveBroker::connectionManager( void ) {
  if ( !ib->isConnected() )
    ib->connect();
}

/*
  Function:     terminateConnection
  Inputs:       None (void)

  Description:
    Signal connection termination
*/
void InteractiveBroker::terminateConnection( void ) {
  if ( isConnected() ) {
    disconnectTrigger = true;
  }

  if ( tProcess ) {
    tProcess->join();
    delete tProcess;
  }

  if ( ib ) {
    delete ib;
    ib = 0;
  }
}

/*
  Functions:    checkResponse
  Inputs:       None (void)
  Outputs:      messageReady (bool)

  Description:
    Check broker queue to see if any responses are ready to be read
*/
bool InteractiveBroker::responseReady( std::string ticker ) {
  bool isReady = false;

  resMtx.lock();
  isReady = response[ticker].isComplete();
  resMtx.unlock();

  return isReady;
}

/*
  Functions:    getResponse
  Inputs:       None (void)

  Description:
    Get the latest updated ticker values prepared by the Interactive
    Broker wrapper
*/
Stock InteractiveBroker::getResponse( std::string ticker ) {
  // Initialize & lock shared variables
  Stock output;
  resMtx.lock();

  // Return if no response is ready
  if ( !response[ticker].isComplete() ) {
    resMtx.unlock();
    return output;
  }

  // Capture response & reset stored data
  output = response[ticker];
  response[ticker].reset();

  // Unlock shared variables
  resMtx.unlock();
  return output;
}
