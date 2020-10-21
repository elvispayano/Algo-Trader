/// Database Request Hyperparam Message
///
/// Message architecture for database request for network layer hyperparameter
/// configuration
///
/// \author   Elvis Payano
/// \date     21/10/2020
/// \version  0.0.1

#ifndef DATABASE_REQUEST_HYPERPARAM_MSG_H
#define DATABASE_REQUEST_HYPERPARAM_MSG_H

// Comms Includes
#include "database_request_msg.h"

class DatabaseRequestHyperparamMsg : public DatabaseRequestMsg {
public:
  /// @fn     DatabaseRequestLayerMsg( void )
  /// @brief  Initialize an empty message structure
  DatabaseRequestHyperparamMsg( void );
  ~DatabaseRequestHyperparamMsg( void ) {}

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

  String ticker;
  uint   index;
  uint   layerNum;

private:
  struct MsgMap {
    Map<String, 0, 0, 6> ticker;
    Map<uint, 6, 0, 0>   index;
    Map<uint, 8, 0, 0>   layerNum;
  } x;

  /// @fn     void write( DatabaseRequestMsg* msg )
  /// @brief  Serialize data and write to the buffer
  void write( DatabaseRequestMsg* msg );

  /// @fn     void read( DatabaseRequestMsg* msg )
  /// @brief  Deserialize data and read from buffer
  void read( DatabaseRequestMsg* msg );
};

#endif /* DATABASE_REQUEST_HYPERPARAM_MSG_H */
