/// Database Response Layer Message
///
/// Base message architecture for transferring packetized layer configuration
/// data
///
/// \author   Elvis Payano
/// \date     16/10/2020
/// \version  0.0.1

#ifndef DATABASE_RESPONSE_LAYER_MSG_H
#define DATABASE_RESPONSE_LAYER_MSG_H

// Comms Includes
#include "database_response_msg.h"

// Utility Includes
#include "utilities/network_types.h"

class DatabaseResponseLayerMsg : public DatabaseResponseMsg {
public:
  DatabaseResponseLayerMsg( void );
  ~DatabaseResponseLayerMsg( void ) {}

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

  String          ticker;
  uint            numberOfInputs;
  uint            numberOfNodes;
  ActivationTypes activation;
  LayerTypes      layer;

private:
  struct MsgMap {
    Map<String, 0, 0, 6>           ticker;
    Map<uint, 6, 0, 0>             numberOfInputs;
    Map<uint, 8, 0, 0>             numberOfNodes;
    Map<ActivationTypes, 10, 0, 0> activation;
    Map<LayerTypes, 11, 0, 0>      layer;
  } x;

  /// @fn     void write( DatabaseResponseMsg* msg )
  /// @brief  Serialize data and write to the buffer
  void write( DatabaseResponseMsg* msg );

  /// @fn     void read( DatabaseResponseMsg* msg )
  /// @brief  Deserialize data and read from buffer
  void read( DatabaseResponseMsg* msg );
};

#endif /* DATABASE_RESPONSE_LAYER_MSG_H */
