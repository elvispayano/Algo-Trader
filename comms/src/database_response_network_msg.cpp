/// Database Response Network Message
///
/// Message architecture for database response with network structure
///
/// \author   Elvis Payano
/// \date     16/10/2020
/// \version  0.0.1

// Comms Includes
#include "comms/database_response_network_msg.h"

/// @fn     DatabaseResponseNetworkMsg( void )
/// @brief  Initialize an empty message structure
DatabaseResponseNetworkMsg::DatabaseResponseNetworkMsg( void ) {
  id      = DatabaseResponseID::NETWORK;
  msgSize = 6;

  ticker.clear();
  layerCount = 0;
}

/// @fn     bool encode( DatabaseResponseMsg* msg )
/// @param  msg   Output message buffer
/// @brief  Serialize the current message and write to the provided message
///         buffer
bool DatabaseResponseNetworkMsg::encode( DatabaseResponseMsg* msg ) {
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
bool DatabaseResponseNetworkMsg::decode( DatabaseResponseMsg* msg ) {
  if ( msg->msgSize > MAX_MSG_SIZE || msg->msgSize != msgSize ) {
    return false;
  }

  read( msg );
  return true;
}

/// @fn     void write( DatabaseResponseMsg* msg )
/// @brief  Serialize data and write to the buffer
void DatabaseResponseNetworkMsg::write( DatabaseResponseMsg* msg ) {
  MsgBase::write( x.ticker, ticker, msg );
  MsgBase::write( x.layerCount, layerCount, msg );
}

/// @fn     void read( DatabaseResponseMsg* msg )
/// @brief  Deserialize data and read from buffer
void DatabaseResponseNetworkMsg::read( DatabaseResponseMsg* msg ) {
  MsgBase::read( x.ticker, ticker, msg );
  MsgBase::read( x.layerCount, layerCount, msg );
}
