/*
  Title:
    Trader

  Description:
    The main trading platform that will house all neural networks. This
    class will process all inputs for each network and capture all actions
    returned by the networks. Once configured this will handle all communication
    between this platform and the SQL database.

  Tests:
    test_trader.cc

  Author:
    Elvis Payano
*/

// Trader Includes
#include "trader.h"

// Interface Includes
#include "broker_base.h"
#include "database_base.h"

// Neural Network Includes
#include "neural_network.h"

/*
  Constructor:    Trader
  Inputs:         None (void)

  Description:
    Initialize the trader and PG objects
*/
Trader::Trader(BrokerBase* brokerIn, DatabaseBase* dbIn, std::vector<NeuralNetwork*>* netIn) :
  broker(brokerIn), database(dbIn), networks(*netIn)
{
  
}

/*
  Destructor:     ~Trader
  Inputs:         None (void)

  Description:
    Ensure proper memory cleanup
*/
Trader::~Trader(void) {
 
}

/*
  Function:     perform
  Inputs:       None (void)

  Description:
    Process neural network inputs
*/
void Trader::perform(void) {

  for (size_t ind = 0; ind < networks.size(); ++ind) {
    // Request Update
    OrderConfig order;
    order.request = Requests::UPDATE;
    order.ticker = networks[ind]->getTicker();

    broker->addToQueue(order);

    // Continue processing if ticker is updated
    if (!broker->responseReady(order.ticker))
      continue;
    
    // Capture broker response in Neural Network input format
    Stock response = broker->getResponse(order.ticker);
    dMatrix input(4, 1, 0.0);
    input(0, 0) = response.getAsk();
    input(1, 0) = response.getBid();
    input(2, 0) = response.getLow();
    input(3, 0) = response.getHigh();

    // Run inputs through network
    //dMatrix output = networks[ind]->process(input);

    // Convert inputs to broker actions

    // Queue broker action

  }
}
