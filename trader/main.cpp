/*
  Title:
    Main

  Description:
    The entrance into the program that will configure all connections as
    expected, run the neural networks, and interface with all external
    applications.

  Author:
    Elvis Payano
*/

// Interface Includes
#include "ib_wrapper.h"
#include "interactive_broker.h"
#include "postgres.h"

// Neural Network Includes
#include "neural_network.h"

// Trader Includes
//#include "trader.h"

// Main Include
#include "main.h"

// Pipeline Automation
#ifdef CI
#include "test_main.h"
#else
#include <qapplication.h>
#include "window_main.h"
#endif

int main(int argc, char **argv) {

#ifdef CI
  // Run Google Test if in debug
  test_main(argc, argv);

  return 0;
#else

  QApplication app(argc, argv);
  
  WindowMain mainWindow;
  mainWindow.show();

  return app.exec();
#endif
}

/*
  Function:     Initialize
  Inputs:       None (void)

  Description:
    Create and configure the trader platform with the required
    settings
*/
//void Initialize(void) {
//  // Initial Variable Setup
//  broker   = 0;
//  database = 0;
//  trader   = 0;
//
//  networks.clear();
//
//  // Configure database connection
//  database = new Postgres("localhost", "5432", "", "", "dbname = trader", "postgres", "password");
//  if (!database->connect())
//    throw(std::runtime_error("Unable to connect to PostgreSQL Database"));
//    
//  // Configure broker connection
//  broker = new InteractiveBroker(new IBWrapper("127.0.0.1", 6550, 0));
//  broker->connectionManager();
//
//  // Configure Neural Networks
//  for (size_t networkCounter = 1; networkCounter <= database->getNetworkCount(); ++networkCounter) {
//    // Get ticker for current network
//    std::string ticker = database->getNetwork(networkCounter);
//
//    // Create and configure network
//    NeuralNetwork* createdNetwork = new NeuralNetwork(ticker);
//    for (size_t layerCounter = 1; layerCounter <= database->getLayerCount(ticker); ++layerCounter)
//      createdNetwork->addLayer(database->getLayer(ticker, layerCounter));
//
//    // Add network to list
//    networks.push_back(createdNetwork);
//  }
//
//  // Configure Trader
//  trader = new Trader(broker, database, &networks);
//
//}
//
///*
//  Functions:    Update
//  Inputs:       None (void)
//  
//  Description:
//    Update trader and take desired actions
//*/
//void Update(void) {
//  trader->perform();
//}
//
///*
//  Function:     Finalize
//  Inputs:       None (void)
//
//  Description:
//    Memory cleanup for all allocated memory
//*/
//void Finalize(void) {
//  if (database) {
//    database->disconnect();
//    delete database;
//  }
//
//  if (broker) {
//    broker->terminateConnection();
//    delete broker;
//  }
//
//  if (trader)
//    delete trader;
//
//  for (size_t it = 0; it < networks.size(); ++it)
//    if (networks[it])
//      delete networks[it];
//}
