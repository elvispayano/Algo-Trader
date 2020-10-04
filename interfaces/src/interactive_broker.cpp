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

/// @fn     void connectionManager
/// @brief  Establish a new connection to the broker interface if one does not
///         exist. If a connnection does exist, do no establish a new one. Runs
///         continously to ensure a valid connection is always available.
void InteractiveBroker::connectionManager( void ) {
  if ( !ib->isConnected() )
    ib->connect();
}

/// @fn     void requestUpdate(  BrokerRequestMsg& msg )
/// @param  msg   Input Message
/// @brief  Request a ticker update
void InteractiveBroker::requestUpdate( BrokerRequestUpdateMsg* msg ) {
  std::string ticker;
  ticker.push_back( msg->s1 );
  ticker.push_back( msg->s2 );
  ticker.push_back( msg->s3 );
  ticker.push_back( msg->s4 );
  ticker.push_back( msg->s5 );
  ticker.push_back( msg->s6 );
  ticker.erase( remove( ticker.begin(), ticker.end(), '\0' ), ticker.end() );

  ib->getCurrentPrice( ticker );
}

/// @fn     void perform( void )
/// @brief  Process request and response messages from Interactive Broker API
void InteractiveBroker::perform( void ) {
  if ( !isConnected() )
    return;
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
Function:     process
Inputs:       None (void)

Description:
Main segment of connection management that will loop and through and
continuously send requests, receive responses, and handle potential
connectivity issues
*/
void InteractiveBroker::process( void ) {
  // Starting Timer
  auto timePrev = std::chrono::system_clock::now();

  // Process Loop
  while ( !disconnectTrigger ) {
    // Update Timer
    std::chrono::duration<double> timeElapsed =
        std::chrono::system_clock::now() - timePrev;

    // No processing at higher than allowed rate (100Hz)
    if ( timeElapsed.count() < 0.01 )
      continue;

    // Update time trigger
    timePrev = std::chrono::system_clock::now();

    // Prevent message processing if no connection is present
    if ( !ib->connect() )
      continue;

    // Receive broker responses every frame
    recvResponse();

    // Send broker requests at 50Hz (max allowed by API)
    if ( frame50 )
      sendRequest();

    // Flip 50Hz frame trigger
    frame50 ^= true;
  }

  // Terminate broker connection when processing is complete
  ib->disconnect();
}

/*
  Function:     recvResponse
  Inputs:       None (void)

  Description:
    Handling responses from the Interactive Broker API.
*/
void InteractiveBroker::recvResponse( void ) {
  ib->processMessages();

  if ( !ib->responseReady() )
    return;

  resMtx.lock();
  Stock output                 = ib->getResponse();
  response[output.getTicker()] = output;
  resMtx.unlock();
}

/*
  Function:     sendRequest
  Inputs:       None (void)

  Description:
    Handling requests made from the trader plaform using the standardize
    format and converting to the appropriate Interactive Broker request
*/
void InteractiveBroker::sendRequest( void ) {
  reqMtx.lock();
  if ( messages.empty() ) {
    reqMtx.unlock();
    return;
  }

  OrderConfig message = messages.front();
  std::string action  = ( message.purchase ) ? "BUY" : "SELL";

  switch ( message.request ) {
  case Requests::UPDATE:
    ib->getCurrentPrice( message.ticker );
    break;

  case Requests::MARKET:
    ib->orderMarket( message.ticker, action, message.quantity );
    break;

  case Requests::LIMIT:
    ib->orderLimit( message.ticker, action, message.quantity, message.price );
    break;

  case Requests::STOP:
    ib->orderStop( message.ticker, action, message.quantity, message.price );
    break;
  }

  messages.pop();
  reqMtx.unlock();
}

/*
  Function:     addToQueue
  Inputs:       message (Stock)

  Description:
    Trading platforms interface to add message to queue. Messages
    will be later read and acted upon by the connection manager
*/
void InteractiveBroker::addToQueue( OrderConfig message ) {
  reqMtx.lock();
  messages.push( message );
  reqMtx.unlock();
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
