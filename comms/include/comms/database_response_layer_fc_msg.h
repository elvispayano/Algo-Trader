/// Database Response Layer Fully Connected Message
///
/// Base message architecture for transferring packetized fully connected layer
/// configuration data
///
/// \author   Elvis Payano
/// \date     16/10/2020
/// \version  0.0.1

#ifndef DATABASE_RESPONSE_LAYER_FC_MSG_H
#define DATABASE_RESPONSE_LAYER_FC_MSG_H

#include "database_response_layer_msg.h"

class DatabaseResponseLayerFCMsg : public DatabaseResponseLayerMsg {
public:
  /// @fn     DatabaseResponseLayerFCMsg( void )
  /// @brief  Initialize an empty message structure
  DatabaseResponseLayerFCMsg( void );
  ~DatabaseResponseLayerFCMsg( void ) {}

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

  struct {
    String ticker;
    uint   layerNum;
  };

private:
  struct MsgMap {
    Map<DbLayerID, 0, 0, 0> layerType;
    Map<String, 1, 0, 6>    ticker;
    Map<uint, 7, 0, 0>      layerNum;
  } x;

  /// @fn     void write( DatabaseResponseMsg* msg )
  /// @brief  Serialize data and write to the buffer
  void write( DatabaseResponseMsg* msg );

  /// @fn     void read( DatabaseResponseMsg* msg )
  /// @brief  Deserialize data and read from buffer
  void read( DatabaseResponseMsg* msg );
};

#endif /* DATABASE_RESPONSE_LAYER_FC_MSG_H */
