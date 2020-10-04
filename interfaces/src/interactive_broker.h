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
  void connectionManager( void ) override;
  void terminateConnection( void ) override;

  // Response Interface
  bool  responseReady( std::string ) override;
  Stock getResponse( std::string ) override;

  // Request Interface
  void addToQueue( OrderConfig message ) override;

  // Connection Management
  void connect( void );

  // Response/Request Interface
  void sendRequest( void );
  void recvResponse( void );
  void process( void );

  bool isConnected( void );

  void perform( void );
  void requestUpdate( BrokerRequestUpdateMsg* msg );

private:

  IBWrapper* ib;
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
