/// Broker Response Update Message
///
/// Message architecture for broker response with ticker updates
///
/// \author   Elvis Payano
/// \date     03/10/2020
/// \version  0.0.1

#ifndef BROKER_RESPONSE_UPDATE_H
#define BROKER_RESPONSE_UPDATE_H

// Comms Includes
#include "broker_response_msg.h"

class BrokerResponseUpdateMsg : public BrokerResponseMsg {
public:
  /// @fn     BrokerResponseUpdateMsg( void )
  /// @brief  Initialize an empty message structure
  BrokerResponseUpdateMsg( void );
  ~BrokerResponseUpdateMsg( void ) {}

  /// @fn     bool encode( BrokerResponseMsg* msg )
  /// @param  msg   Output message buffer
  /// @brief  Serialize the current message and write to the provided message
  ///         buffer
  bool encode( BrokerResponseMsg* msg ) override;

  /// @fn     bool decode( BrokerResponseMsg* msg )
  /// @param  msg   Input message buffer
  /// @brief  Deserialize the provided message buffer and populate the current
  ///         message with the corresponding data
  bool decode( BrokerResponseMsg* msg ) override;

  float  bid;
  float  ask;
  float  last;
  float  high;
  float  low;
  String ticker;

private:
  struct MsgMap {
    Map<float, 0, 0, 1>   bid;
    Map<float, 4, 0, 1>   ask;
    Map<float, 8, 0, 1>   last;
    Map<float, 12, 0, 1>  high;
    Map<float, 16, 0, 1>  low;
    Map<String, 20, 0, 6> ticker;
  } x;

  /// @fn     void write( BrokerResponseMsg* msg )
  /// @brief  Serialize data and write to the buffer
  void write( BrokerResponseMsg* msg );

  /// @fn     void read( BrokerResponseMsg* msg )
  /// @brief  Deserialize data and read from buffer
  void read( BrokerResponseMsg* msg );
};

#endif /* BROKER_RESPONSE_UPDATE_H */
