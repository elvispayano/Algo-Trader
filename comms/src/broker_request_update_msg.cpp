/// Broker Request Update Message
///
/// Message architecture for requesting ticker updates from the broker API
///
/// \author   Elvis Payano
/// \date     03/10/2020
/// \version  0.0.1

// Comms Includes
#include "comms/broker_request_update_msg.h"

/// @fn     BrokerRequestUpdateMsg( void )
/// @brief  Initialize an empty message structure
BrokerRequestUpdateMsg::BrokerRequestUpdateMsg( void ) {
  id      = RequestID::UPDATE;
  msgSize = 6;

  s1 = '\0';
  s2 = '\0';
  s3 = '\0';
  s4 = '\0';
  s5 = '\0';
  s6 = '\0';
}

/// @fn     bool encode( BrokerRequestMsg& msg )
/// @param  msg   Output message buffer
/// @brief  Serialize the current message and write to the provided message
///         buffer
bool BrokerRequestUpdateMsg::encode( BrokerRequestMsg* msg ) {
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
bool BrokerRequestUpdateMsg::decode( BrokerRequestMsg* msg ) {
  if ( msg->msgSize > MAX_MSG_SIZE || msg->msgSize != msgSize ) {
    return false;
  }

  read( msg );
  return true;
}

/// @fn     void write( BrokerRequestMsg& msg )
/// @brief  Serialize data and write to the buffer
void BrokerRequestUpdateMsg::write( BrokerRequestMsg* msg ) {
  MsgBase::write( x.s1, s1, msg );
  MsgBase::write( x.s2, s2, msg );
  MsgBase::write( x.s3, s3, msg );
  MsgBase::write( x.s4, s4, msg );
  MsgBase::write( x.s5, s5, msg );
  MsgBase::write( x.s6, s6, msg );
}

/// @fn     void read( BrokerRequestMsg& msg )
/// @brief  Deserialize data and read from buffer
void BrokerRequestUpdateMsg::read( BrokerRequestMsg* msg ) {
  MsgBase::read( x.s1, s1, msg );
  MsgBase::read( x.s2, s2, msg );
  MsgBase::read( x.s3, s3, msg );
  MsgBase::read( x.s4, s4, msg );
  MsgBase::read( x.s5, s5, msg );
  MsgBase::read( x.s6, s6, msg );
}
