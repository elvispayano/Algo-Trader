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

// Standard Includes
#include <string>

// Forward Declaration
class IBWrapper;

class InteractiveBroker : public BrokerBase {
public:
  // Constructor
  InteractiveBroker(IBWrapper* wrapper, std::string host, int port, int clientID);
  
  // Destructor
  ~InteractiveBroker(void);

  // Connection management
  bool connect(void) override;
  void disconnect(void) override;

  void updateTicker(std::string ticker) override;

private:
  IBWrapper* ib;
  std::string host;
  int port;
  int clientID;
  bool isConnected;
};

#endif /* INTERACTIVE_BROKER_H */
