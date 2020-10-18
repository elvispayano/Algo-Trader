/// Database Request Layer Message
///
/// Message architecture for database request with netowkr layer configuration
///
/// \author   Elvis Payano
/// \date     18/10/2020
/// \version  0.0.1

#ifndef DATABASE_REQUEST_LAYER_MSG_H
#define DATABASE_REQUEST_LAYER_MSG_H

// Comms Includes
#include "database_request_msg.h"

class DatabaseRequestLayerMsg : public DatabaseRequestMsg {
public:
  /// @fn     DatabaseRequestLayerMsg( void )
  /// @brief  Initialize an empty message structure
  DatabaseRequestLayerMsg( void );
  ~DatabaseRequestLayerMsg( void ) {}

  /// @fn     bool encode( DatabaseRequestMsg* msg )
  /// @param  msg   Output message buffer
  /// @brief  Serialize the current message and write to the provided message
  ///         buffer
  bool encode( DatabaseRequestMsg* msg ) override;

  /// @fn     bool decode( DatabaseRequestMsg* msg )
  /// @param  msg   Input message buffer
  /// @brief  Deserialize the provided message buffer and populate the current
  ///         message with the corresponding data
  bool decode( DatabaseRequestMsg* msg ) override;

  struct {
    String ticker;
    uint   layerNumber;
  };

private:
  struct MsgMap {
    Map<String, 0, 0, 6> ticker;
    Map<uint, 6, 0, 0>   layerNumber;
  } x;

  /// @fn     void write( DatabaseRequestMsg* msg )
  /// @brief  Serialize data and write to the buffer
  void write( DatabaseRequestMsg* msg );

  /// @fn     void read( DatabaseRequestMsg* msg )
  /// @brief  Deserialize data and read from buffer
  void read( DatabaseRequestMsg* msg );
};

#endif /* DATABASE_REQUEST_LAYER_MSG_H */
