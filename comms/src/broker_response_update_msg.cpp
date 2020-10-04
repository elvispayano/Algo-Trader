/// Broker Response Update MEssage
///
/// Message architecture for broker response with ticker updates
///
/// \author   Elvis Payano
/// \date     03/10/2020
/// \version  0.0.1

// Comms Includes
#include "comms/broker_response_update_msg.h"

/// @fn     BrokerRequestUpdateMsg( void )
/// @brief  Initialize an empty message structure
BrokerResponseUpdateMsg::BrokerResponseUpdateMsg( void ) {
  id      = ResponseID::UPDATE;
  msgSize = 6;

  bid  = 0.0f;
  ask  = 0.0f;
  low  = 0.0f;
  high = 0.0f;
  last = 0.0f;
}

/// @fn     bool encode( BrokerRequestMsg& msg )
/// @param  msg   Output message buffer
/// @brief  Serialize the current message and write to the provided message
///         buffer
bool BrokerResponseUpdateMsg::encode( BrokerResponseMsg* msg ) {
  if ( msg->msgSize > MAX_MSG_SIZE ) {
    return false;
  }
  msg->msgSize = msgSize;
  msg->setID( id );
  write( msg );
  return true;
}

/// @fn     bool decode( BrokerRequestMsg& msg )
/// @param  msg   Input message buffer
/// @brief  Deserialize the provided message buffer and populate the current
///         message with the corresponding data
bool BrokerResponseUpdateMsg::decode( BrokerResponseMsg* msg ) {
  if ( msg->msgSize > MAX_MSG_SIZE || msg->msgSize != msgSize ) {
    return false;
  }

  read( msg );
  return true;
}

/// @fn     void write( BrokerRequestMsg& msg )
/// @brief  Serialize data and write to the buffer
void BrokerResponseUpdateMsg::write( BrokerResponseMsg* msg ) {
  MsgBase::write( x.bid, bid, msg );
  MsgBase::write( x.ask, ask, msg );
  MsgBase::write( x.last, last, msg );
  MsgBase::write( x.high, high, msg );
  MsgBase::write( x.low, low, msg );
}

/// @fn     void read( BrokerRequestMsg& msg )
/// @brief  Deserialize data and read from buffer
void BrokerResponseUpdateMsg::read( BrokerResponseMsg* msg ) {
  MsgBase::read( x.bid, bid, msg );
  MsgBase::read( x.ask, ask, msg );
  MsgBase::read( x.last, last, msg );
  MsgBase::read( x.high, high, msg );
  MsgBase::read( x.low, low, msg );
}
