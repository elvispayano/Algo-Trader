// Algo-Trader Includes
#include "database_controller.h"
#include "data_server.h"

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

  for ( unsigned int i = 0; i < pDatabase->getNetworkCount();  ++i) {
    unsigned int netID = i + 1;
    pServer->addNetwork( pDatabase->getNetwork( netID ) );
  }

  pDatabase->performInput();

  pDatabase->update();

  pDatabase->performOutput();
}
