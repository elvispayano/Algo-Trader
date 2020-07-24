#ifndef MOCK_NEURAL_NETWORK_H
#define MOCK_NEURAL_NETWORK_H

// Neural Network Includes
#include "neural_network.h"

// Utility Includes
#include "matrix.h"

// Google Mock Includes
#include <gmock/gmock.h>

// Standard Includes
#include <string>

class MockNeuralNetwork : public NeuralNetwork {
public:
  MockNeuralNetwork(std::string ticker) : NeuralNetwork(ticker) {}
  MOCK_METHOD1(process, dMatrix(dMatrix));
  MOCK_METHOD0(getTicker, std::string(void));

};

#endif /* MOCK_NEURAL_NETWORK_H */
