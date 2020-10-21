/// Broker Response Message
///
/// Base message architecture for transferring packetized broker response data
///
/// \author   Elvis Payano
/// \date     03/10/2020
/// \version  0.0.1

#ifndef BROKER_RESPONSE_MSG_H
#define BROKER_RESPONSE_MSG_H

#include "msg_base.h"

enum class ResponseID { UPDATE, UNKNOWN };

class BrokerResponseMsg : public MsgBase {
public:
  BrokerResponseMsg( void ) { id = ResponseID::UNKNOWN; }
  ~BrokerResponseMsg( void ) {}

  virtual bool encode( BrokerResponseMsg* msg ) { return false; }
  virtual bool decode( BrokerResponseMsg* msg ) { return false; }

  ResponseID getID( void ) { return id; }
  void       setID( ResponseID in ) { id = in; }

protected:
  ResponseID id;
};

#endif /* BROKER_RESPONSE_MSG_H */
