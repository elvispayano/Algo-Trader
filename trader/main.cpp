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

// Main Include
#include "main.h"

// Debug configuration execution
#ifdef TESTS
#include "test_main.h"
#endif

int main(int argc, char **argv) {

#ifdef TESTS
  // Run Google Test if in debug
  test_main(argc, argv);
  return 0;
#endif
  
  Initialize();
  
  //for (size_t it = 1; it <= database->getNetworkCount(); ++it) {
  //  std::string ticker = database->getNetwork(it);
  //  NeuralNetwork* x = new NeuralNetwork(ticker);
  //  for (size_t tt = 1; tt <= database->getLayerCount(ticker); ++tt)
  //    x->addLayer(database->getLayer(ticker, tt));
  //}
  
  Finalize();

  return 0;
}

/*
  Function:     Initialize
  Inputs:       None (void)

  Description:
    Create and configure the trader platform with the required
    settings
*/
void Initialize(void) {
  database = 0;
  networks.clear();

  // Configure database connection
  database = new Postgres("localhost", "5432", "", "", "dbname = postgres", "postgres", "password");
  if (!database->connect())
    throw(std::runtime_error("Unable to connect to PostgreSQL Database"));
    
  // Configure broker connection
  wrapper = new IBWrapper("127.0.0.1", 6550, 0);
  broker = new InteractiveBroker(wrapper);
  broker->connectionManager();
}

/*
  Function:     Finalize
  Inputs        None (void)

  Description:
    Memory cleanup for all allocated memory
*/
void Finalize(void) {
  if (database)
    delete database;

  if (broker)
    delete broker;

  if (wrapper)
    delete wrapper;

  for (size_t it = 0; it < networks.size(); ++it)
    if (networks[it])
      delete networks[it];
}
