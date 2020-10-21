/// Database Request Layer Message
///
/// Message architecture for database request with netowkr layer configuration
///
/// \author   Elvis Payano
/// \date     18/10/2020
/// \version  0.0.1

// Comms Includes
#include "comms/database_request_hyperparam_msg.h"

/// @fn     DatabaseRequestLayerMsg( void )
/// @brief  Initialize an empty message structure
DatabaseRequestHyperparamMsg::DatabaseRequestHyperparamMsg( void ) {
  id      = DatabaseRequestID::HYPERPARAM;
  msgSize = 10;

  ticker.clear();
  index    = 0;
  layerNum = 0;
}

/// @fn     bool encode( DatabaseRequestMsg* msg )
/// @param  msg   Output message buffer
/// @brief  Serialize the current message and write to the provided message
///         buffer
bool DatabaseRequestHyperparamMsg::encode( DatabaseRequestMsg* msg ) {
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
bool DatabaseRequestHyperparamMsg::decode( DatabaseRequestMsg* msg ) {
  if ( msg->msgSize > MAX_MSG_SIZE || msg->msgSize != msgSize ) {
    return false;
  }

  read( msg );
  return true;
}

/// @fn     void write( DatabaseRequestMsg* msg )
/// @brief  Serialize data and write to the buffer
void DatabaseRequestHyperparamMsg::write( DatabaseRequestMsg* msg ) {
  MsgBase::write( x.ticker, ticker, msg );
  MsgBase::write( x.index, index, msg );
  MsgBase::write( x.layerNum, layerNum, msg );
}

/// @fn     void read( DatabaseRequestMsg* msg )
/// @brief  Deserialize data and read from buffer
void DatabaseRequestHyperparamMsg::read( DatabaseRequestMsg* msg ) {
  MsgBase::read( x.ticker, ticker, msg );
  MsgBase::read( x.index, index, msg );
  MsgBase::read( x.layerNum, layerNum, msg );
}
