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
#include "utilities/fifo_bidirectional.h"
#include "utilities/stock.h"

// Standard Includes
#include <string>

// Forward Declaration
class BrokerRequestUpdateMsg;
class BrokerRequestMsg;
class BrokerResponseMsg;

class BrokerBase {
public:
  BrokerBase( void ){};   // Constructor
  ~BrokerBase( void ){};  // Destructor

  virtual void
  install( FIFOBidirectional<BrokerResponseMsg, BrokerRequestMsg>* port ) = 0;

  /// @fn     void performInput( void )
  /// @brief  Process all received inputs received from broker
  virtual void performInput( void ) = 0;

  /// @fn     void performOutput( void )
  /// @brief  Send all outgoing messages to broker
  virtual void performOutput( void ) = 0;

  /// @fn     bool isConnected( void )
  /// @brief  Check if a valid broker connection is established
  virtual bool isConnected( void ) = 0;

  /// @fn     void connect( void )
  /// @brief  Create a new connection if one is not established
  virtual void connect( void ) = 0;
};

#endif /* BROKER_BASE_H */
