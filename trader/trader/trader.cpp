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
Trader::Trader(BrokerBase* brokerIn, DatabaseBase* dbIn, std::vector<NeuralNetwork*> netIn) :
  broker(brokerIn), database(dbIn)
{
  networks.clear();
  networks = netIn;
}

/*
  Destructor:     ~Trader
  Inputs:         None (void)

  Description:
    Ensure proper memory cleanup
*/
Trader::~Trader(void) {
  for (size_t i = 0; i < networks.size(); ++i)
    if (networks[i]) delete networks[i];
  networks.clear();
}

/*
  Function:     setup
  Inputs:       None (void)

  Description:
    Configure the trader with all the requisite neural networks
*/
void Trader::setup(void) {

  for (size_t i = 1; i <= database->getNetworkCount(); ++i) {
    // Create a new network
    std::string ticker = database->getNetwork(i);
    NeuralNetwork* net = new NeuralNetwork(ticker);

    // Configure network
    for (size_t layerNum = 1; layerNum <= database->getLayerCount(ticker); ++layerNum) {
      net->addLayer(database->getLayer(ticker, layerNum));
      }
    
    // Add network to vector
    networks.push_back(net);
  }
}

/*
  Function:     perform
  Inputs:       None (void)

  Description:
    Process neural network inputs
*/
void Trader::perform(void) {
  for (size_t ind = 0; ind < networks.size(); ++ind) {
    // Capture Inputs (TBD)
    dMatrix input;

    // Run inputs through network
    networks[ind]->process(input);
  }
}
