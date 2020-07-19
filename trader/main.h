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

// Standard Includes
#include <vector>

// Forward Declaration
class BrokerBase;
class IBWrapper;
class DatabaseBase;
class NeuralNetwork;
class Trader;

// Object Creation
DatabaseBase* database;
BrokerBase*   broker;
IBWrapper*    wrapper;
std::vector<NeuralNetwork*> networks;
Trader*       trader;

void Initialize(void);
void Finalize(void);
