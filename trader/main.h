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
class Postgres;
class NeuralNetwork;

// Object Creation
Postgres* database;
std::vector<NeuralNetwork*> networks;
