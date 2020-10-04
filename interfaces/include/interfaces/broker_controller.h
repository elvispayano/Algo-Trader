#ifndef BROKER_CONTROLLER_H
#define BROKER_CONTROLLER_H

// Forward Declarationi
class BrokerBase;
class BrokerRequestMsg;
class BrokerRequestUpdateMsg;
class BrokerResponseMsg;
class BrokerResponseUpdateMsg;

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

  BrokerRequestMsg*       bReqMsg;
  BrokerRequestUpdateMsg* bReqUpdateMsg;

  BrokerResponseMsg*       bResMsg;
  BrokerResponseUpdateMsg* bResUpdateMsg;
};

#endif /* BROKER_CONTROLLER_H */
