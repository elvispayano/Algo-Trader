#ifndef DATABASE_CONTROLLER_H
#define DATABASE_CONTROLLER_H

// Comms Includes
#include "comms/database_request_msg.h"
#include "comms/database_request_layer_msg.h"
#include "comms/database_response_msg.h"
#include "comms/layer_msg.h"

// Utility Includes
#include "utilities/fifo_bidirectional.h"

// Forward Declarations
class Postgres;
class DataServer;

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
  ///                       DatabaseRequestMsg>* port )
  /// @param  port  Installed database port
  /// @brief  Provide the database interface with the installed communication
  ///         port.
  void
  install( FIFOBidirectional<DatabaseResponseMsg, DatabaseRequestMsg>* port );

private:

  /// @fn     void processInputs( void )
  /// @brief  Process broker and database inputs
  void processInputs( void );

  /// @fn     void writeMessage( DatabaseResponseMsg msg )
  /// @param  msg   Message to write to buffer
  /// @brief  Write the database response message
  void writeMessage( DatabaseResponseMsg msg );

  /// @fn     void updateNetworks( void )
  /// @brief  Determine which networks should be loaded by the project
  void updateNetworks( void );

  /// @fn     void requestLayerConfiguration( void )
  /// @brief  
  void requestLayerConfiguration( void );

  DataServer* pServer;
  Postgres*   pDatabase;

  FIFOBidirectional<DatabaseResponseMsg, DatabaseRequestMsg>* pPort;

  DatabaseResponseMsg databaseResponse;

  DatabaseRequestLayerMsg reqLayerMsg;
};

#endif /* DATABASE_CONTROLLER_H */
