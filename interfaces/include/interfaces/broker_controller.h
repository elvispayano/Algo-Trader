#ifndef BROKER_CONTROLLER_H
#define BROKER_CONTROLLER_H

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
};

#endif /* BROKER_CONTROLLER_H */
