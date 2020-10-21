/// Database Response Layer Message
///
/// Base message architecture for transferring packetized layer configuration
/// data
///
/// \author   Elvis Payano
/// \date     16/10/2020
/// \version  0.0.1

// Comms Includes
#include "comms/database_response_layer_msg.h"

/// @fn     DatabaseResponseNetworkMsg( void )
/// @brief  Initialize an empty message structure
DatabaseResponseLayerMsg::DatabaseResponseLayerMsg( void ) {
  id      = DatabaseResponseID::LAYER;
  msgSize = 12;

  ticker.clear();
  numberOfInputs = 0;
  numberOfNodes  = 0;
  activation     = ActivationTypes::UNKNOWN;
  layer          = LayerTypes::UNKNOWN;
}

/// @fn     bool encode( DatabaseResponseMsg* msg )
/// @param  msg   Output message buffer
/// @brief  Serialize the current message and write to the provided message
///         buffer
bool DatabaseResponseLayerMsg::encode( DatabaseResponseMsg* msg ) {
  if ( msg->msgSize > MAX_MSG_SIZE ) {
    return false;
  }
  msg->msgSize = msgSize;
  msg->setID( id );
  write( msg );
  return true;
}

/// @fn     bool decode( DatabaseResponseMsg* msg )
/// @param  msg   Input message buffer
/// @brief  Deserialize the provided message buffer and populate the current
///         message with the corresponding data
bool DatabaseResponseLayerMsg::decode( DatabaseResponseMsg* msg ) {
  if ( msg->msgSize > MAX_MSG_SIZE || msg->msgSize != msgSize ) {
    return false;
  }

  read( msg );
  return true;
}

/// @fn     void write( DatabaseResponseMsg* msg )
/// @brief  Serialize data and write to the buffer
void DatabaseResponseLayerMsg::write( DatabaseResponseMsg* msg ) {
  MsgBase::write( x.ticker, ticker, msg );
  MsgBase::write( x.numberOfInputs, numberOfInputs, msg );
  MsgBase::write( x.numberOfNodes, numberOfNodes, msg );
  MsgBase::write( x.activation, activation, msg );
  MsgBase::write( x.layer, layer, msg );
}

/// @fn     void read( DatabaseResponseMsg* msg )
/// @brief  Deserialize data and read from buffer
void DatabaseResponseLayerMsg::read( DatabaseResponseMsg* msg ) {
  MsgBase::read( x.ticker, ticker, msg );
  MsgBase::read( x.numberOfInputs, numberOfInputs, msg );
  MsgBase::read( x.numberOfNodes, numberOfNodes, msg );
  MsgBase::read( x.activation, activation, msg );
  MsgBase::read( x.layer, layer, msg );
}
