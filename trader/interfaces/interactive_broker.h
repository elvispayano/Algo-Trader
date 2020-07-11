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
#include <string>
#include <thread>
#include <vector>

// Forward Declaration
class IBWrapper;

class InteractiveBroker : public BrokerBase {
public:
  // Constructor
  InteractiveBroker(IBWrapper* wrapper);
  
  // Destructor
  ~InteractiveBroker(void);

  // Connection management
  bool connect(void) override;
  void disconnect(void) override;
  void connectionManager(void);

  void updateTicker(std::string ticker) override;
  void addMessage(Stock message);

private:
  void sendRequest(void);
  void recvResponse(void);
  void process(void);
  

  IBWrapper* ib;
  bool isConnected;
  std::vector<Stock> requests;
  std::thread* tProcess;
  bool disconnectTrigger;
};

#endif /* INTERACTIVE_BROKER_H */
