/// Database Response Message
///
/// Base message architecture for transferring packetized database response data
///
/// \author   Elvis Payano
/// \date     16/10/2020
/// \version  0.0.1

#ifndef DATABASE_RESPONSE_MSG_H
#define DATABASE_RESPONSE_MSG_H

// Comms Includes
#include "msg_base.h"

enum class DatabaseResponseID { HYPERPARAM, LAYER, NETWORK, UNKNOWN };

class DatabaseResponseMsg : public MsgBase {
public:
  DatabaseResponseMsg( void ) { id = DatabaseResponseID::UNKNOWN; }
  ~DatabaseResponseMsg( void ) {}

  virtual bool encode( DatabaseResponseMsg* msg ) { return false; }
  virtual bool decode( DatabaseResponseMsg* msg ) { return false; }

  DatabaseResponseID getID( void ) { return id; }
  void               setID( DatabaseResponseID in ) { id = in; }

protected:
  DatabaseResponseID id;
};

#endif /* DATABASE_RESPONSE_MSG_H */
