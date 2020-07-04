
// Interface Includes
#include "ib_wrapper.h"
#include "interactive_broker.h"

InteractiveBroker::InteractiveBroker(void) {
  ib = new IBWrapper();
}

InteractiveBroker::~InteractiveBroker(void) {
  if (ib)
    delete ib;
}

bool InteractiveBroker::connect(void) {
  return false;
}

void InteractiveBroker::disconnect(void) {

}