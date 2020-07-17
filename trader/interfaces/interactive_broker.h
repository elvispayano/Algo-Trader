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
#include "broker_base.h"

// Utility Includes
#include "broker_types.h"
#include "stock.h"

// Standard Includes
#include <mutex>
#include <queue>
#include <string>
#include <thread>

// Forward Declaration
class IBWrapper;

class InteractiveBroker : public BrokerBase {
public:
  // Constructor
  InteractiveBroker(IBWrapper* wrapper);
  
  // Destructor
  ~InteractiveBroker(void);

  // Connection management
  void connectionManager(void) override;

  // Response Interface
  bool responseReady(void) override;
  void getResponse(Stock&) override;

  // Request Interface
  void addToQueue(OrderConfig message) override;

private:
  // Connection Management
  bool connect(void);
  void disconnect(void);

  // Response/Request Interface
  void sendRequest(void);
  void recvResponse(void);
  void process(void);
  
  IBWrapper* ib;
  bool isConnected;
  bool disconnectTrigger;
  bool frame50;
  
  std::queue<OrderConfig> messages;
  std::queue<Stock>       response;
  std::mutex              reqMtx;
  std::mutex              resMtx;
  std::thread*            tProcess;
};

#endif /* INTERACTIVE_BROKER_H */
