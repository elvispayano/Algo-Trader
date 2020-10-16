#ifndef DATABASE_CONTROLLER_H
#define DATABASE_CONTROLLER_H

// Comms Includes
#include "comms/database_response_msg.h"
#include "comms/layer_msg.h"

// Utility Includes
#include "utilities/fifo_bidirectional.h"

// Forward Declarations
class Postgres;
class DataServer;

// Port Forward Declarations
class LayerMsg;

class DatabaseController {
public:
  DatabaseController( DataServer* server );
  ~DatabaseController( void );

  /// @fn     void initialize( void )
  /// @brief  Initialize the broker controller with the configured settings
  void initialize( void );

  /// @fn     void perform( void )
  /// @brief  Perform a database controller update
  void perform( void );

  /// @fn     void install( FIFOBidirectional<DatabaseResponseMsg,
  ///                       LayerMsg>* port )
  /// @param  port  Installed database port
  /// @brief  Provide the database interface with the installed communication
  ///         port.
  void install( FIFOBidirectional<DatabaseResponseMsg, LayerMsg>* port );

private:

  /// @fn     void writeMessage( DatabaseResponseMsg msg )
  void writeMessage( DatabaseResponseMsg msg );

  void updateNetworks( void );

  DataServer* pServer;
  Postgres*   pDatabase;

  FIFOBidirectional<DatabaseResponseMsg, LayerMsg>* pBrokerPort;

  DatabaseResponseMsg databaseResponse;
};

#endif /* DATABASE_CONTROLLER_H */
