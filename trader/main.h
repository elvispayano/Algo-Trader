
// Interface Includes
#include "postgres.h"

// Neural Network Includes
#include "neural_network.h"

// Standard Includes
#include <vector>

// Forward Declaration
class Postgres;
class NeuralNetwork;

// Object Creation
Postgres* database;
std::vector<NeuralNetwork*> networks;