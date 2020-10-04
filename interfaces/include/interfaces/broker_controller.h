#ifndef BROKER_CONTROLLER_H
#define BROKER_CONTROLLER_H

// Comms Includes
#include "comms/broker_request_msg.h"
#include "comms/broker_request_update_msg.h"

class BrokerBase;

class BrokerController {
public:
  BrokerController( void );
  ~BrokerController( void );

  void initialize( void );
  void perform( void );

private:
  void processInputs( void );
  void update( void );
  void processOutputs( void );

  BrokerBase* pBroker;

  BrokerRequestMsg       brokerMsg;
  BrokerRequestUpdateMsg brokerUpdateMsg;
};

#endif /* BROKER_CONTROLLER_H */
