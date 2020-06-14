﻿/*
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
#include "pg_layer.h"
#include "pg_network.h"

// Neural Network Includes
#include "neural_network.h"

/*
  Constructor:    Trader
  Inputs:         None (void)

  Description:
    Initialize the trader and PG objects
*/
Trader::Trader(void) {
  pgN = new PGNetwork();
  pgL = new PGLayer();
  
  networks.clear();
}

/*
  Destructor:     ~Trader
  Inputs:         None (void)

  Description:
    Ensure proper memory cleanup
*/
Trader::~Trader(void) {
  if (pgN) delete pgN;
  if (pgL) delete pgL;

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
  pgN->connect();
  pgL->connect();

  for (size_t i = 1; i <= pgN->networkCount(); ++i) {
    // Create a new network
    NeuralNetwork* net = new NeuralNetwork;

    char* ticker = pgN->getNetwork(i);
    net->setTicker(ticker);

    for (size_t layerNum = 1; layerNum <= pgN->layerCount(ticker); ++layerNum)
      net->addLayer(pgL->getLayer(ticker, layerNum));
    
    // Add network to vector
    networks.push_back(net);
  }

  pgN->disconnect();
  pgL->disconnect();
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
