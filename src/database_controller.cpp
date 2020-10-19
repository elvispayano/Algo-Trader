// Algo-Trader Includes
#include "database_controller.h"
#include "data_server.h"

// Comms Includes
#include "comms/database_response_layer_msg.h"
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
///                       DatabaseRequestMsg>* port )
/// @param  port  Installed database port
/// @brief  Provide the database interface with the installed communication
///         port.
void DatabaseController::install(
    FIFOBidirectional<DatabaseResponseMsg, DatabaseRequestMsg>* port ) {
  pPort = port;
}

/// @fn     void initialize( void )
/// @brief  Initialize the database controller with the configured settings
void DatabaseController::initialize( void ) {
  pDatabase = new Postgres( "192.168.50.50",
                            "5432",
                            "",
                            "",
                            "dbname = postgres",
                            "postgres",
                            "password" );
}

/// @fn     void perform( void )
/// @brief  Perform a database controller update
void DatabaseController::perform( void ) {
  // Check Connection Status
  if ( !pDatabase->isConnected() ) {
    pDatabase->connect();
    return;
  }

  processInputs();

  updateNetworks();
}

/// @fn     void writeMessage( DatabaseResponseMsg msg )
/// @param  msg   Message to write to buffer
/// @brief  Write the database response message
void DatabaseController::writeMessage( DatabaseResponseMsg msg ) {
  if ( !pPort->putInput( msg ) ) {
    printf( "DatabaseCntl: Error Writing To Bus\n" );
  }
}

/// @fn     void updateNetworks( void )
/// @brief  Determine which networks should be loaded by the project
void DatabaseController::updateNetworks( void ) {
  DatabaseResponseNetworkMsg            networkMsg;
  std::map<std::string, NeuralNetwork*> networkList = pServer->getNetworkList();

  std::vector<std::string> dbList;
  for ( unsigned int i = 1; i <= pDatabase->getNetworkCount(); ++i ) {
    dbList.push_back( pDatabase->getNetwork( i ) );
  }

  // Add networks
  for ( std::string ticker : dbList ) {
    if ( networkList.find( ticker ) != networkList.end() ) {
      continue;
    }

    networkMsg.ticker     = ticker;
    networkMsg.layerCount = pDatabase->getLayerCount( networkMsg.ticker );
    networkMsg.action     = DbNetworkID::ADD;
    if ( networkMsg.encode( &databaseResponse ) ) {
      writeMessage( databaseResponse );
    }
    break;
  }

  // Delete networks
  for ( auto& network : networkList ) {
    if ( dbList.end() !=
         std::find( dbList.begin(), dbList.end(), network.first ) ) {
      continue;
    }

    networkMsg.ticker = network.first;
    networkMsg.action = DbNetworkID::REMOVE;
    if ( networkMsg.encode( &databaseResponse ) ) {
      writeMessage( databaseResponse );
    }
  }
}

/// @fn     void processInputs( void )
/// @brief  Process broker and database inputs
void DatabaseController::processInputs( void ) {
  DatabaseRequestMsg request;
  if ( !pPort->getOutput( request ) ) {
    return;
  }

  switch ( request.getID() ) {
  case DatabaseRequestID::LAYER:
    if ( reqLayerMsg.decode( &request ) ) {
      requestLayerConfiguration();
    }
    break;

  default:
    printf( "DatabaseCtrl: Invalid Request Message\n" );
  }
}

void DatabaseController::requestLayerConfiguration( void ) {
  DatabaseResponseLayerMsg response;

  std::string  ticker   = reqLayerMsg.ticker;
  unsigned int layerNum = reqLayerMsg.layerNumber;

  response.ticker         = reqLayerMsg.ticker;
  response.numberOfInputs = pDatabase->getInputs( ticker, layerNum );
  response.numberOfNodes  = pDatabase->getNodes( ticker, layerNum );
  response.activation     = pDatabase->getActivation( ticker, layerNum );
  response.layer          = pDatabase->getLayerType( ticker, layerNum );

  if ( response.encode( &databaseResponse ) ) {
    writeMessage( databaseResponse );
  }
}
