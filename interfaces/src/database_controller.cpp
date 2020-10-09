#include "interfaces/database_controller.h"
#include "postgres.h"

DatabaseController::DatabaseController( void ) {
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

  pDatabase->performInput();

  pDatabase->performOutput();
}
