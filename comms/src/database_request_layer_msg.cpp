/// Database Request Layer Message
///
/// Message architecture for database request with netowkr layer configuration
///
/// \author   Elvis Payano
/// \date     18/10/2020
/// \version  0.0.1

// Comms Includes
#include "comms/database_request_layer_msg.h"

/// @fn     DatabaseRequestLayerMsg( void )
/// @brief  Initialize an empty message structure
DatabaseRequestLayerMsg::DatabaseRequestLayerMsg( void ) {
  id      = DatabaseRequestID::LAYER;
  msgSize = 7;

  ticker.clear();
  layerNumber = 0;
}

/// @fn     bool encode( DatabaseRequestMsg* msg )
/// @param  msg   Output message buffer
/// @brief  Serialize the current message and write to the provided message
///         buffer
bool DatabaseRequestLayerMsg::encode( DatabaseRequestMsg* msg ) {
  if ( msg->msgSize > MAX_MSG_SIZE ) {
    return false;
  }
  msg->msgSize = msgSize;
  msg->setID( id );
  write( msg );
  return true;
}

/// @fn     bool decode( DatabaseRequestMsg* msg )
/// @param  msg   Input message buffer
/// @brief  Deserialize the provided message buffer and populate the current
///         message with the corresponding data
bool DatabaseRequestLayerMsg::decode( DatabaseRequestMsg* msg ) {
  if ( msg->msgSize > MAX_MSG_SIZE || msg->msgSize != msgSize ) {
    return false;
  }

  read( msg );
  return true;
}

/// @fn     void write( DatabaseRequestMsg* msg )
/// @brief  Serialize data and write to the buffer
void DatabaseRequestLayerMsg::write( DatabaseRequestMsg* msg ) {
  MsgBase::write( x.ticker, ticker, msg );
  MsgBase::write( x.layerNumber, layerNumber, msg );
}

/// @fn     void read( DatabaseRequestMsg* msg )
/// @brief  Deserialize data and read from buffer
void DatabaseRequestLayerMsg::read( DatabaseRequestMsg* msg ) {
  MsgBase::read( x.ticker, ticker, msg );
  MsgBase::read( x.layerNumber, layerNumber, msg );
}
