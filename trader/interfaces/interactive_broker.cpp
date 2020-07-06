
// Interface Includes
#include "ib_wrapper.h"
#include "interactive_broker.h"

InteractiveBroker::InteractiveBroker(std::string host, int port, int clientID) : 
  host(host), port(port), clientID(clientID) {

  ib = new IBWrapper();
}

InteractiveBroker::~InteractiveBroker(void) {
  if (ib)
    delete ib;
}

bool InteractiveBroker::connect(void) {
  return ib->connect(host.c_str(), port, clientID);
}

void InteractiveBroker::disconnect(void) {
  ib->disconnect();
}

void InteractiveBroker::getPrice(void) {
  ib->getLast();
}
