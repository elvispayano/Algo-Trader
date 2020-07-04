
#ifndef INTERACTIVE_BROKER_H
#define INTERACTIVE_BROKER_H

// Interface Includes
#include "broker_base.h"

// Forward Declaration
class IBWrapper;

class InteractiveBroker : public BrokerBase {
public:
  InteractiveBroker(void);
  ~InteractiveBroker(void);

  bool connect(void);
  void disconnect(void);

private:
  IBWrapper* ib;
};

#endif /* INTERACTIVE_BROKER_H */