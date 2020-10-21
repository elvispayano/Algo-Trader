/// Database Response Network Message
///
/// Message architecture for database response with network structure
///
/// \author   Elvis Payano
/// \date     16/10/2020
/// \version  0.0.1

#ifndef DATABASE_RESPONSE_NETWORK_MSG_H
#define DATABASE_RESPONSE_NETWORK_MSG_H

// Comms Includes
#include "database_response_msg.h"

enum class DbNetworkID { ADD, REMOVE, UNKNOWN };

class DatabaseResponseNetworkMsg : public DatabaseResponseMsg {
public:
  /// @fn     DatabaseResponseNetworkMsg( void )
  /// @brief  Initialize an empty message structure
  DatabaseResponseNetworkMsg( void );
  ~DatabaseResponseNetworkMsg( void ) {}

  /// @fn     bool encode( BrokerResponseMsg* msg )
  /// @param  msg   Output message buffer
  /// @brief  Serialize the current message and write to the provided message
  ///         buffer
  bool encode( DatabaseResponseMsg* msg ) override;

  /// @fn     bool decode( BrokerResponseMsg* msg )
  /// @param  msg   Input message buffer
  /// @brief  Deserialize the provided message buffer and populate the current
  ///         message with the corresponding data
  bool decode( DatabaseResponseMsg* msg ) override;

  String      ticker;
  uint        layerCount;
  DbNetworkID action;

private:
  struct MsgMap {
    Map<String, 0, 0, 6>      ticker;
    Map<uint, 6, 0, 0>        layerCount;
    Map<DbNetworkID, 7, 0, 0> action;
  } x;

  /// @fn     void write( DatabaseResponseMsg* msg )
  /// @brief  Serialize data and write to the buffer
  void write( DatabaseResponseMsg* msg );

  /// @fn     void read( DatabaseResponseMsg* msg )
  /// @brief  Deserialize data and read from buffer
  void read( DatabaseResponseMsg* msg );
};

#endif /* DATABASE_RESPONSE_NETWORK_MSG_H */
