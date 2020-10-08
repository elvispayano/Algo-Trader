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

#ifndef INTERACTIVE_BROKER_H
#define INTERACTIVE_BROKER_H

// Comms Includes
#include "comms/broker_request_update_msg.h"

// Interface Includes
#include "interfaces/broker_base.h"

// Utility Includes
#include "utilities/broker_types.h"
#include "utilities/stock.h"

// Standard Includes
#include <map>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

// Forward Declaration
class IBWrapper;

class InteractiveBroker : public BrokerBase {
public:
  // Constructor
  InteractiveBroker( IBWrapper* wrapper );

  // Destructor
  ~InteractiveBroker( void );

  // Connection management
  void connectionManager( void ); // TODO: Delete this line
  void terminateConnection( void ); // TODO: Delete this line

  // Response Interface
  bool  responseReady( std::string ); // TODO: Delete this line
  Stock getResponse( std::string ); // TODO: Delete this line

  /// @fn     void connect( void )
  /// @brief  Create a new connection if one is not established
  void connect( void );

  /// @fn     bool isConnected( void )
  /// @brief  Check if a valid broker connection is established
  bool isConnected( void );

  /// @fn     void performInput( void )
  /// @brief  Process inputs from the broker API
  void performInput( void );

  /// @fn     void performOutput( void )
  /// @brief  Process outputs from the broker API
  void performOutput( void );

  /// @fn     void requestUpdate( BrokerRequestUpdateMsg* msg )
  /// @param  msg   Message sent to Broker API
  /// @brief  Request a ticker update from the broker
  void requestUpdate( BrokerRequestUpdateMsg* msg );

  void requestMarketPurchase() {}
  void requestMarketSell() {}
  void requestLimitPurchase() {}
  void requestLimitSell() {}
  void requestStopPurchase() {}
  void requestStopSell() {}

  /// @fn     void install( FIFOBidirectional< BrokerRequestMsg,
  ///                       BrokerRequestMsg >* port )
  /// @param  port  Installed broker port
  /// @brief  Provide the broker interface with the installed communication
  ///         port.
  void install( FIFOBidirectional<BrokerResponseMsg, BrokerRequestMsg>* port );

private:

  IBWrapper* ib;
  BrokerRequestUpdateMsg bReqUpdateMsg;

  FIFOBidirectional<BrokerResponseMsg, BrokerRequestMsg>* pPort;


  bool       disconnectTrigger;
  bool       frame50;

  // Requests
  std::mutex                reqMtx;
  std::queue< OrderConfig > messages;

  // Responses
  std::mutex                     resMtx;
  std::map< std::string, Stock > response;

  // Threads
  std::thread* tProcess;
};

#endif /* INTERACTIVE_BROKER_H */
