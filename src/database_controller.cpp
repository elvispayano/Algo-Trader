// Algo-Trader Includes
#include "database_controller.h"
#include "data_server.h"

// Comms Includes
#include "comms/database_response_network_msg.h"

// Interface Includes
#include "postgres.h"

DatabaseController::DatabaseController( DataServer* server )
    : pServer( server ) {
  pDatabase = 0;

  initialize();
}

DatabaseController::~DatabaseController( void ) {
  if ( pDatabase ) {
    delete pDatabase;
  }
}

/// @fn     void install( FIFOBidirectional<DatabaseResponseMsg,
///                       LayerMsg>* port )
/// @param  port  Installed database port
/// @brief  Provide the database interface with the installed communication
///         port.
void DatabaseController::install(
    FIFOBidirectional<DatabaseResponseMsg, LayerMsg>* port ) {
  pBrokerPort = port;
}

/// @fn     void initialize( void )
/// @brief  Initialize the database controller with the configured settings
void DatabaseController::initialize( void ) {
  pDatabase = new Postgres(
      "localhost", "5432", "", "", "dbname = trader", "postgres", "password" );
}

/// @fn     void perform( void )
/// @brief  Perform a database controller update
void DatabaseController::perform( void ) {
  // Check Connection Status
  if ( !pDatabase->isConnected() ) {
    pDatabase->connect();
    return;
  }

  createNetworks();
}

void DatabaseController::writeMessage( DatabaseResponseMsg msg ) {
  if ( !pBrokerPort->putInput( msg ) ) {
    printf( "DatabaseCntl: Error Writing To Bus\n" );
  }
}

void DatabaseController::createNetworks( void ) {
  DatabaseResponseNetworkMsg            networkMsg;
  std::map<std::string, NeuralNetwork*> networkList = pServer->getNetworkList();

  static unsigned int count      = 0;
  unsigned int        netID      = networkList.size();
  unsigned int        totalCount = pDatabase->getNetworkCount();

  // Find missing networks
  if ( count < totalCount ) {
    for (unsigned int i = 1; i <= totalCount; ++i) {
      networkMsg.ticker = pDatabase->getNetwork( i );
      if ( networkList.find( networkMsg.ticker ) != networkList.end() ) {
        continue;
      }
      
      networkMsg.layerCount = pDatabase->getLayerCount( networkMsg.ticker );
      if ( networkMsg.encode( &databaseResponse ) ) {
        writeMessage( databaseResponse );
      }
      break;
    }
  }
}
