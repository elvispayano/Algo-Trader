
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
  InteractiveBroker(std::string host, int port, int clientID);
  ~InteractiveBroker(void);

  bool connect(void) override;
  void disconnect(void) override;

  void getPrice(void) override;

private:
  IBWrapper* ib;
  std::string host;
  int port;
  int clientID;
};

#endif /* INTERACTIVE_BROKER_H */