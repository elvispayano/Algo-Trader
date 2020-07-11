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
#include <chrono>
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
  
  while (!isConnected && !connected && counter < 3) {
    ++counter;
    connected = ib->connect();
  }

  isConnected = connected;
  return isConnected;
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
void InteractiveBroker::updateTicker(std::string ticker) {
  ib->getCurrentPrice(ticker);
  return;
  if (!isConnected) {
    throw std::logic_error("Connect Error: Can not request from IB API without a valid connection");
  }
}

/*
  Function:     connectionManager
  Inputs:       None (void)

  Description:
    Start the broker connecion manager. Once started, keep the connection
    established until signaled to terminate. Running connection on a separate
    thread to allow for continuous updates
*/
void InteractiveBroker::connectionManager(void) {
  if (!connect())
    throw std::runtime_error("Connection Error: Unable to connect to Interactive Broker API");
  
  tProcess = new std::thread(std::bind(&InteractiveBroker::process, this));
}

/*
  Function:     process
  Inputs:       None (void)

  Description:
    Main segment of connection management that will loop and through and
    continuously send requests, receive responses, and handle potential
    connectivity issues
*/
void InteractiveBroker::process(void) {
  auto now = std::chrono::system_clock::now();
  
  while (!disconnectTrigger) {
    std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - now;
    if (elapsed_seconds.count() < 0.05)
      continue;
    now = std::chrono::system_clock::now();

    if (!ib->connect())
      continue;

    recvResponse();
    sendRequest();
  }
  
  ib->disconnect();
}

/*
  Function:     recvResponse
  Inputs:       None (void)

  Description:
    Handling responses from the Interactive Broker API.
*/
void InteractiveBroker::recvResponse(void) {
  ib->processMessages();
}

/*
  Function:     sendRequest
  Inputs:       None (void)

  Description:
    Handling requests made from the trader plaform using the standardize
    format and converting to the appropriate Interactive Broker request
*/
void InteractiveBroker::sendRequest(void) {
  reqMtx.lock();
  if (requests.empty()) {
    reqMtx.unlock();
    return;
  }
  Stock req = requests.back();
  switch (req.getAction()) {
  case Requests::UPDATE:
    ib->getCurrentPrice(req.getTicker());
    break;

  case Requests::SELL:
    break;

  case Requests::BUY:
    break;

  }
  
  requests.pop_back();
  reqMtx.unlock();
}

/*
  Function:     addToQueue
  Inputs:       message (Stock)

  Description:
    Trading platforms interface to add message to queue. Messages
    will be later read and acted upon by the connection manager
*/
void InteractiveBroker::addToQueue(Stock message) {
  reqMtx.lock();
  requests.push_back(message);
  reqMtx.unlock();
}
