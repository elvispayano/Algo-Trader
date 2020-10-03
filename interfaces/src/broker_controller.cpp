#include "interfaces/broker_controller.h"

BrokerController::BrokerController( void ) {}

BrokerController::~BrokerController( void ) {}

void BrokerController::perform( void ) {
  processInputs();

  update();

  processOutputs();
}
