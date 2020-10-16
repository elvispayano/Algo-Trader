/// Database Response Layer Fully Connected Message
///
/// Base message architecture for transferring packetized fully connected layer
/// configuration data
///
/// \author   Elvis Payano
/// \date     16/10/2020
/// \version  0.0.1

// Comms Includes
#include "comms/database_response_layer_fc_msg.h"

/// @fn     DatabaseResponseNetworkMsg( void )
/// @brief  Initialize an empty message structure
DatabaseResponseLayerFCMsg::DatabaseResponseLayerFCMsg( void ) {
  id      = DatabaseResponseID::LAYER;
  msgSize = 8;

  ticker.clear();
  layerType = DbLayerID::FULLYCONNECTED;
}

/// @fn     bool encode( DatabaseResponseMsg* msg )
/// @param  msg   Output message buffer
/// @brief  Serialize the current message and write to the provided message
///         buffer
bool DatabaseResponseLayerFCMsg::encode( DatabaseResponseMsg* msg ) {
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
bool DatabaseResponseLayerFCMsg::decode( DatabaseResponseMsg* msg ) {
  if ( msg->msgSize > MAX_MSG_SIZE || msg->msgSize != msgSize ) {
    return false;
  }

  read( msg );
  return true;
}

/// @fn     void write( DatabaseResponseMsg* msg )
/// @brief  Serialize data and write to the buffer
void DatabaseResponseLayerFCMsg::write( DatabaseResponseMsg* msg ) {
  MsgBase::write( x.layerType, layerType, msg );
  MsgBase::write( x.ticker, ticker, msg );
  MsgBase::write( x.layerNum, layerNum, msg );
}

/// @fn     void read( DatabaseResponseMsg* msg )
/// @brief  Deserialize data and read from buffer
void DatabaseResponseLayerFCMsg::read( DatabaseResponseMsg* msg ) {
  MsgBase::read( x.layerType, layerType, msg );
  MsgBase::read( x.ticker, ticker, msg );
  MsgBase::read( x.layerNum, layerNum, msg );
}
