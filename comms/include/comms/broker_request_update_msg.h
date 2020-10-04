/// Broker Request Update Message
///
/// Message architecture for requesting ticker updates from the broker API
///
/// \author   Elvis Payano
/// \date     03/10/2020
/// \version  0.0.1

#ifndef BROKER_REQUEST_UPDATE_H
#define BROKER_REQUEST_UPDATE_H

// Comms Includes
#include "broker_request_msg.h"

class BrokerRequestUpdateMsg : public BrokerRequestMsg {
public:
  /// @fn     BrokerRequestUpdateMsg( void )
  /// @brief  Initialize an empty message structure
  BrokerRequestUpdateMsg( void );
  ~BrokerRequestUpdateMsg( void ) {}

  /// @fn     bool encode( BrokerRequestMsg& msg )
  /// @param  msg   Output message buffer
  /// @brief  Serialize the current message and write to the provided message
  ///         buffer
  bool encode( BrokerRequestMsg& msg ) override;

  /// @fn     bool decode( BrokerRequestMsg& msg )
  /// @param  msg   Input message buffer
  /// @brief  Deserialize the provided message buffer and populate the current
  ///         message with the corresponding data
  bool decode( BrokerRequestMsg& msg ) override;

  struct {
    char s1;
    char s2;
    char s3;
    char s4;
    char s5;
    char s6;
  };

private:
  struct MsgMap {
    Map<char, 0, 0, 0> s1;
    Map<char, 1, 0, 0> s2;
    Map<char, 2, 0, 0> s3;
    Map<char, 3, 0, 0> s4;
    Map<char, 4, 0, 0> s5;
    Map<char, 5, 0, 0> s6;
  } x;

  /// @fn     void write( BrokerRequestMsg& msg )
  /// @brief  Serialize data and write to the buffer
  void write( BrokerRequestMsg& msg );

  /// @fn     void read( BrokerRequestMsg& msg )
  /// @brief  Deserialize data and read from buffer
  void read( BrokerRequestMsg& msg );
};

#endif /* BROKER_REQUEST_UPDATE_H */
