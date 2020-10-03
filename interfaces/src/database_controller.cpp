#include "interfaces/database_controller.h"

DatabaseController::DatabaseController( void ) {}

DatabaseController::~DatabaseController( void ) {}

void DatabaseController::perform( void ) {
  processInputs();

  update();

  processOutputs();
}
