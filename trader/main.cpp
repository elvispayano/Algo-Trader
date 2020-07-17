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
#endif
  database = 0;
  networks.clear();

  // Configure database connection
  database = new Postgres("localhost", "5432", "", "", "dbname = postgres", "postgres", "password");
  database->connect();

  // Configure broker connection
  wrapper = new IBWrapper("127.0.0.1", 6550, 0);
  broker = new InteractiveBroker(wrapper);

  
  for (size_t it = 1; it <= database->getNetworkCount(); ++it) {
    std::string ticker = database->getNetwork(it);
    NeuralNetwork* x = new NeuralNetwork(ticker);
    for (size_t tt = 1; tt <= database->getLayerCount(ticker); ++tt)
      x->addLayer(database->getLayer(ticker, tt));
  }
  
  // Memory Cleanup
  if (database)
    delete database;

  if (broker)
    delete broker;

  for (size_t it = 0; it < networks.size(); ++it)
    if (networks[it])
      delete networks[it];

  return 0;
}
