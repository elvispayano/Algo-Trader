#include "neural_network.h"
#include "gtest/gtest.h"

#include "matrix.h"
#include "network_types.h"

class NeuralNetworkTest : public ::testing::Test {
protected:
  void SetUp(void) override {
    config.Activation = ActivationTypes::SIGMOID;
  }

public:
  NeuralNetwork network;
  LayerConfiguration config;
};

TEST_F(NeuralNetworkTest, AddLayers) {
  EXPECT_EQ(0, network.getLayerCount());

  network.addLayer(config);
  EXPECT_EQ(1, network.getLayerCount());

  network.addLayer(config);
  EXPECT_EQ(2, network.getLayerCount());
}
