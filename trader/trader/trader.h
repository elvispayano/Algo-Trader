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

#ifndef TRADER_H
#define TRADER_H

// Standard Includes
#include <vector>

// Forward Declarations
class BrokerBase;
class DatabaseBase;
class NeuralNetwork;

class Trader {
public:
  // Constructor
  Trader(BrokerBase* brokerIn, DatabaseBase* dbIn, std::vector<NeuralNetwork*>* netIn);

  // Destructor
  ~Trader(void);

  // Trader Interface
  void perform(void);

private:
  BrokerBase*   broker;
  DatabaseBase* database;
  std::vector<NeuralNetwork*> networks;
};

#endif /* TRADER_H */
