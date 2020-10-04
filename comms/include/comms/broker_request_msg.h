/// Broker Request Message
///
/// Base message architecture for transferring packetized broker request data
///
/// \author   Elvis Payano
/// \date     03/10/2020
/// \version  0.0.1

#ifndef BROKER_REQUEST_MSG_H
#define BROKER_REQUEST_MSG_H

#include "msg_base.h"

enum class RequestID {
  UPDATE,
  MARKETPURCHASE,
  MARKETSELL,
  LIMITPURCHASE,
  LIMITSELL,
  STOPPURCHASE,
  STOPSELL,
  UNKNOWN
};

class BrokerRequestMsg : public MsgBase {
public:
  BrokerRequestMsg( void ) { id = RequestID::UNKNOWN; }
  ~BrokerRequestMsg( void ) {}

  virtual bool encode( BrokerRequestMsg& msg ) { return false; }
  virtual bool decode( BrokerRequestMsg& msg ) { return false; }

  RequestID getID( void ) { return id; }
  void      setID( RequestID in ) { id = in; }

protected:
  RequestID id;
};

#endif /* BROKER_REQUEST_MSG_H */
