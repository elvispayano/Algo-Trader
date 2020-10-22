/// Database Response Hyperparam Message
///
/// Base message architecture for transferring packetized hyperparameter
/// configuration data
///
/// \author   Elvis Payano
/// \date     21/10/2020
/// \version  0.0.1

// Comms Includes
#include "comms/database_response_hyperparam_msg.h"

/// @fn     DatabaseResponseNetworkMsg( void )
/// @brief  Initialize an empty message structure
DatabaseResponseHyperparamMsg::DatabaseResponseHyperparamMsg( void ) {
  id      = DatabaseResponseID::HYPERPARAM;
  msgSize = 14;

  ticker.clear();
  layerNum = 0;
  index    = 0;
  value    = 0.0f;
}

/// @fn     bool encode( DatabaseResponseMsg* msg )
/// @param  msg   Output message buffer
/// @brief  Serialize the current message and write to the provided message
///         buffer
bool DatabaseResponseHyperparamMsg::encode( DatabaseResponseMsg* msg ) {
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
bool DatabaseResponseHyperparamMsg::decode( DatabaseResponseMsg* msg ) {
  if ( msg->msgSize > MAX_MSG_SIZE || msg->msgSize != msgSize ) {
    return false;
  }

  read( msg );
  return true;
}

/// @fn     void write( DatabaseResponseMsg* msg )
/// @brief  Serialize data and write to the buffer
void DatabaseResponseHyperparamMsg::write( DatabaseResponseMsg* msg ) {
  MsgBase::write( x.ticker, ticker, msg );
  MsgBase::write( x.layerNum, layerNum, msg );
  MsgBase::write( x.index, index, msg );
  MsgBase::write( x.value, value, msg );
}

/// @fn     void read( DatabaseResponseMsg* msg )
/// @brief  Deserialize data and read from buffer
void DatabaseResponseHyperparamMsg::read( DatabaseResponseMsg* msg ) {
  MsgBase::read( x.ticker, ticker, msg );
  MsgBase::read( x.layerNum, layerNum, msg );
  MsgBase::read( x.index, index, msg );
  MsgBase::read( x.value, value, msg );
}
