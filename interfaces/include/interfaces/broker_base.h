/*
  Title:
    Broker Base

  Description:
    This class is the template configuration for managing connections to
  external brokers applications. This base implementation will allow for the
  selected solution to be independent of how the project is designed.

  Test:
    test_broker_base.cc

  Author:
    Elvis Payano
*/

#ifndef BROKER_BASE_H
#define BROKER_BASE_H

// Utility Includes
#include "utilities/broker_types.h"
#include "utilities/stock.h"

// Standard Includes
#include <string>

// Forward Declaration
class BrokerRequestUpdateMsg;

class BrokerBase {
public:
  BrokerBase( void ){};   // Constructor
  ~BrokerBase( void ){};  // Destructor

  // Connection management
  virtual void connectionManager( void ) = 0;

  // Request Interface
  virtual void addToQueue( OrderConfig message ) = 0;

  // Response Interface
  virtual bool  responseReady( std::string ) = 0;
  virtual Stock getResponse( std::string )   = 0;

  virtual void perform( void ) = 0;

  // New Interface
  virtual bool isConnected( void )                          = 0;
  virtual void connect( void )                              = 0;
  virtual void requestUpdate( BrokerRequestUpdateMsg* msg ) = 0;
  virtual void requestMarketPurchase( void ) {}
  virtual void requestMarketSell( void ) {}
  virtual void requestLimitPurchase( void ) {}
  virtual void requestLimitSell( void ) {}
  virtual void requestStopPurchase( void ) {}
  virtual void requestStopSell( void ) {}

private:
  virtual void terminateConnection( void ) = 0;
};

#endif /* BROKER_BASE_H */
