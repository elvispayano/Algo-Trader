/// Database Response Layer Message
///
/// Base message architecture for transferring packetized layer configuration
/// data
///
/// \author   Elvis Payano
/// \date     16/10/2020
/// \version  0.0.1

#ifndef DATABASE_RESPONSE_LAYER_MSG_H
#define DATABASE_RESPONSE_LAYER_MSG_H

// Comms Includes
#include "database_response_msg.h"

enum class DbLayerID { FULLYCONNECTED, UNKNOWN };

class DatabaseResponseLayerMsg : public DatabaseResponseMsg {
public:
  DatabaseResponseLayerMsg( void ) { layerType = DbLayerID::UNKNOWN; }
  ~DatabaseResponseLayerMsg( void ) {}

protected:
  DbLayerID layerType;
};

#endif /* DATABASE_RESPONSE_LAYER_MSG_H */
