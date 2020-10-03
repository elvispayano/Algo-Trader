#ifndef BROKER_CONTROLLER_H
#define BROKER_CONTROLLER_H

class BrokerController {
public:
  BrokerController( void );
  ~BrokerController( void );

  void perform( void );

private:
  void processInputs( void ) {}
  void update( void ) {}
  void processOutputs( void ) {}
};

#endif /* BROKER_CONTROLLER_H */
