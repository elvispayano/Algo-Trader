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

class BrokerBase {
public:
  BrokerBase(void) {};  // Constructor
  ~BrokerBase(void) {}; // Destructor

  // Connection management
  virtual bool connect(void) = 0;
  virtual void disconnect(void) = 0;

  virtual void getPrice(void) = 0;
};

#endif /* BROKER_BASE_H */