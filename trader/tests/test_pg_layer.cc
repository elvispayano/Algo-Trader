/*
  Title:
    PG Layer Unit Test

  Description:
    This unit test will call expected SQL functionality pertaining to the
    neural network layer configuration and return expected values from a
    test database

  Author:
    Elvis Payano
*/

// Interface Includes
#include "pg_layer.h"

// Google Test Includes
#include <gtest/gtest.h>

// Unit Test Framework Setup
class PGLayerTest :
  public ::testing::Test,
  public PGLayer {
protected:
  // Ensure each test has a properly configured connection
  // to the postgres database
  void SetUp(void) override {
    setDatabase("dbname = gtest");
    setPort("5431");
    connect();
    ASSERT_EQ(getStatus(), ConnStatusType::CONNECTION_OK);
    getLayer("MSFT", 1);
  }
};

/*
  Test:         Inputs
  Description:
    Ensure expected results using the SQL "layer_inputs" function
*/
TEST_F(PGLayerTest, Inputs) {
  EXPECT_EQ(4, getInputs());
}

/*
  Test:         Nodes
  Description:
    Ensure expected results using the SQL "layer_nodes" function
*/
TEST_F(PGLayerTest, Nodes) {
  EXPECT_EQ(2, getNodes());
}

/*
  Test:         Index
  Description:
    Ensure expected results using the SQL "layer_ind" function
*/
TEST_F(PGLayerTest, Index) {
  EXPECT_EQ(1, getInd());
}

/*
  Test:         LayerType
  Description:
    Ensure expected results using the SQL "layer_type" function
*/
TEST_F(PGLayerTest, LayerType) {
  EXPECT_EQ(LayerTypes::FULLYCONNECTED, getLayerType());
}

/*
  Test:         ActivationType
  Description:
    Ensure expected results using the SQL "activation_type" function
*/
TEST_F(PGLayerTest, ActivationType) {
  EXPECT_EQ(ActivationTypes::RELU, getActivationType());
}

/*
  Test:         Configuration
  Description:
    Ensure expected results are formatted properly within the layer
    configuration output
*/
TEST_F(PGLayerTest, Configuration) {
  LayerConfiguration capture = getLayer("MSFT", 1);

  EXPECT_EQ(4, capture.layerWidth);
  EXPECT_EQ(2, capture.layerHeight);
  EXPECT_EQ(1, capture.offset);
  EXPECT_EQ(LayerTypes::FULLYCONNECTED, capture.Layer);
  EXPECT_EQ(ActivationTypes::RELU, capture.Activation);
}
