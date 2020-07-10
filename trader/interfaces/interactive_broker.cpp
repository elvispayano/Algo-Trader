/*
  Title:
    Interactive Broker

  Description:
    This class is responsbile for configuring and managing the Interactive
    Broker connection. The main objective of this call is to ensure that all
    requests are properly fulfilled

  Test:
    test_interactive_broker.cc

  Author:
    Elvis Payano
*/

// Interface Includes
#include "ib_wrapper.h"
#include "interactive_broker.h"

// Standard Includes
#include <functional>

/*
  Constructor:  InteractiveBroker
  Inputs:       wrapper (IBWrapper*), host (string), port (int), clientID (int)

  Description:
    Setup configuration for Interactive Broker connection
*/
InteractiveBroker::InteractiveBroker(IBWrapper* wrapper) : ib(wrapper) {
  isConnected = false;
  disconnectTrigger = false;
  tProcess = 0;
}

/*
  Desctructor:  ~InteractiveBroker
  Inputs:       None (void)

  Description:
    Ensure Interactive Broker connection is safely terminated during object
    destruction
*/
InteractiveBroker::~InteractiveBroker(void) {
  disconnect();
}

/*
  Function:     connect
  Inputs:       None (void)
  Outputs:      connectionEstablished (bool)

  Description:
    Attempt to establish a connection to an Interactive Broker API using the
    configured parameters
*/
bool InteractiveBroker::connect(void) {
  bool connected = false;
  size_t counter = 0;

  if (isConnected)
    return true;
  
  while (!connected && counter < 3) {
    ++counter;
    connected = ib->connect();
  }
  if (!connected) {
    return false;
  }

  isConnected = true;
  return true;
}

/*
  Function:     disconnect
  Inputs:       None (void)
  
  Description:
    Expected procedure for safe termination of a connection to the Interactive
    Broker API.
*/
void InteractiveBroker::disconnect(void) {
  if (isConnected) {
    disconnectTrigger = true;
    isConnected = false;
  }
  if (tProcess)
    tProcess->join();
}

/*
  Function:     updateTicker
  Inputs:       ticker (string)

  Description:
    Request latest values for the provided ticker
*/
Stock InteractiveBroker::updateTicker(std::string ticker) {
  return ib->getCurrentPrice(ticker);
  if (!isConnected) {
    throw std::logic_error("Connect Error: Can not request from IB API without a valid connection");
  }
}

void InteractiveBroker::connectionManager(void) {
  if (!connect())
    throw std::runtime_error("Connection Error: Unable to connect to Interactive Broker API");
  
  tProcess = new std::thread(std::bind(&InteractiveBroker::process, this));
}

#include <chrono>
void InteractiveBroker::process(void) {
  auto now = std::chrono::system_clock::now();
  
  while (!disconnectTrigger) {
    std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - now;
    if (elapsed_seconds.count() < 0.05)
      continue;
    now = std::chrono::system_clock::now();
    recvResponse();
    sendRequest(1);
  }
  
  ib->disconnect();
}

void InteractiveBroker::recvResponse(void) {
  ib->processMessages();
}

void InteractiveBroker::sendRequest(int i) {
  if (requests.empty())
    return;

  requests.pop_back();
  ib->getCurrentPrice("MSFT");
}