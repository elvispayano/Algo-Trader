// trader.cpp : Defines the entry point for the application.
//
#ifdef DEBUG
#include "test_main.h"
#endif

#include "main.h"

int main(int argc, char **argv) {
#ifdef DEBUG
  test_main();
  return 0;
#endif
  database = 0;
  networks.clear();

  // Configure database connection
  database = new Postgres("localhost", "5432", "", "", "dbname = postgres", "postgres", "password");
  if (!database->connect())
    return 1;
  int x = database->getNetworkCount();
  for (size_t it = 1; it <= database->getNetworkCount(); ++it) {
    std::string ticker = database->getNetwork(it);
    NeuralNetwork* x = new NeuralNetwork(ticker);
    for (size_t tt = 1; tt <= database->getLayerCount(ticker); ++tt)
      x->addLayer(database->getLayer(ticker, tt));
  }
  
  // Memory Cleanup
  if (database) delete database;
  for (size_t it = 0; it < networks.size(); ++it)
    if (networks[it])
      delete networks[it];

  return 0;
}
