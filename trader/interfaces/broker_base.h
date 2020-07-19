/*
  Title:
    Broker Base

  Description:
    This class is the template configuration for managing connections to external
    brokers applications. This base implementation will allow for the selected solution to be
    independent of how the project is designed.

  Test:
    test_broker_base.cc

  Author:
    Elvis Payano
*/

#ifndef BROKER_BASE_H
#define BROKER_BASE_H

// Utility Includes
#include "broker_types.h"
#include "stock.h"

// Standard Includes
#include <string>

class BrokerBase {
public:
  BrokerBase(void) {};  // Constructor
  ~BrokerBase(void) {}; // Destructor

  // Connection management
  virtual void connectionManager(void) = 0;

  // Request Interface
  virtual void addToQueue(OrderConfig message) = 0;

  // Response Interface
  virtual bool responseReady(void) = 0;
  virtual void getResponse(Stock&) = 0;
};

#endif /* BROKER_BASE_H */
