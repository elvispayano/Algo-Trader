/// Layer Message
///
/// Base message architecture for transferring packetized layer configuration
/// data
///
/// \author   Elvis Payano
/// \date     02/10/2020
/// \version  0.0.1

#ifndef LAYER_MSG_H
#define LAYER_MSG_H

#include "msg_base.h"

enum class LayerID { UNKNOWN, FULLYCONNECTED };

class LayerMsg : public MsgBase {
public:
  LayerMsg( void ) { id = LayerID::UNKNOWN; }
  ~LayerMsg( void ) {}

  virtual bool encode( LayerMsg& msg ) { return false; }
  virtual bool decode( LayerMsg& msg ) { return false; }

  LayerID getID( void ) { return id; }

protected:
  LayerID id;
};

#endif /* LAYER_MSG_H */
