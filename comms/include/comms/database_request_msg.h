/// Database Request Layer Message
///
/// Base message architecture for transferring packetizes layer configuration
/// request data
///
/// \author   Elvis Payano
/// \date     18/10/2020
/// \version  0.0.1

#ifndef DATABASE_REQUEST_MSG_H
#define DATABASE_REQUEST_MSG_H

// Comms Includes
#include "msg_base.h"

enum class DatabaseRequestID { LAYER, UNKNOWN };

class DatabaseRequestMsg : public MsgBase {
public:
  DatabaseRequestMsg( void ) { id = DatabaseRequestID::UNKNOWN; }
  ~DatabaseRequestMsg( void ) {}

  virtual bool encode( DatabaseRequestMsg* msg ) { return false; }
  virtual bool decode( DatabaseRequestMsg* msg ) { return false; }

  DatabaseRequestID getID( void ) { return id; }
  void              setID( DatabaseRequestID in ) { id = in; }

protected:
  DatabaseRequestID id;
};

#endif /* DATABASE_REQUEST_MSG_H */
