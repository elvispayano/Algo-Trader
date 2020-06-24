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
#include "pg_connect.h"

// Utility Includes
#include "matrix.h"

// Standard Includes
#include <string>

// Google Test Includes
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Google Test Mocked Classes
class MockPGConnect : public PGConnect {
public:
  MOCK_METHOD3(execFunc, char*(std::string, char*, int));
  MOCK_METHOD1(pg2i, int (std::string));
  MOCK_METHOD1(pg2f, float (std::string));
};

// Unit Test Framework Setup
class PGLayerTest : public ::testing::Test {
protected:
  void SetUp(void) override {
    mock = new MockPGConnect;
    pg = new PGLayer(mock);
  }

  void TearDown(void) override {
    if (mock)
      delete mock;
    if (pg)
      delete pg;
  }

public:
  MockPGConnect* mock;
  PGLayer* pg;

  std::string valueStr = "5";
  int value = 5;
  std::string function;
};

/*
  Test:         Inputs
  Description:
    Ensure expected results using the SQL "layer_inputs" function
*/
TEST_F(PGLayerTest, Inputs) {
  function = "layer_inputs";
  EXPECT_CALL(*mock, execFunc(function, static_cast<char*>(NULL), 0)).Times(1).WillOnce(::testing::Return(static_cast<char*>("5")));
  EXPECT_CALL(*mock, pg2i(valueStr)).Times(1).WillOnce(::testing::Return(5));
  EXPECT_EQ(value, pg->getInputs());
}

/*
  Test:         Nodes
  Description:
    Ensure expected results using the SQL "layer_nodes" function
*/
TEST_F(PGLayerTest, Nodes) {
  function = "layer_nodes";
  EXPECT_CALL(*mock, execFunc(function, static_cast<char*>(NULL), 0)).Times(1).WillOnce(::testing::Return(static_cast<char*>("5")));
  EXPECT_CALL(*mock, pg2i(valueStr)).Times(1).WillOnce(::testing::Return(5));
  EXPECT_EQ(value, pg->getNodes());
}

/*
  Test:         Index
  Description:
    Ensure expected results using the SQL "layer_ind" function
*/
TEST_F(PGLayerTest, Index) {
  function = "layer_ind";
  EXPECT_CALL(*mock, execFunc(function, static_cast<char*>(NULL), 0)).Times(1).WillOnce(::testing::Return(static_cast<char*>("5")));
  EXPECT_CALL(*mock, pg2i(valueStr)).Times(1).WillOnce(::testing::Return(5));
  EXPECT_EQ(value, pg->getInd());
}

/*
  Test:         LayerType
  Description:
    Ensure expected results using the SQL "layer_type" function
*/
TEST_F(PGLayerTest, LayerType) {
  function = "layer_type";
  EXPECT_CALL(*mock, execFunc(function, static_cast<char*>(NULL), 0)).Times(1).WillOnce(::testing::Return(static_cast<char*>("5")));
  EXPECT_CALL(*mock, pg2i(valueStr)).Times(1).WillOnce(::testing::Return(0));
  EXPECT_EQ(LayerTypes::FULLYCONNECTED, pg->getLayerType());
}

/*
  Test:         ActivationType
  Description:
    Ensure expected results using the SQL "activation_type" function
*/
TEST_F(PGLayerTest, ActivationType) {
  function = "layer_activation";
  EXPECT_CALL(*mock, execFunc(function, static_cast<char*>(NULL), 0)).Times(1).WillOnce(::testing::Return(static_cast<char*>("5")));
  EXPECT_CALL(*mock, pg2i(valueStr)).Times(1).WillOnce(::testing::Return(2));
  EXPECT_EQ(ActivationTypes::RELU, pg->getActivationType());
}

/*
  Test:         Weight
  Description:
    Ensure expected results using the SQL "get_wb" function
*/
TEST_F(PGLayerTest, Weight) {
  // Weight Height Config
  function = "layer_nodes";
  EXPECT_CALL(*mock, execFunc(function, static_cast<char*>(NULL), 0)).Times(1).WillOnce(::testing::Return(static_cast<char*>("5")));
  // Weight Width Config
  function = "layer_inputs";
  EXPECT_CALL(*mock, execFunc(function, static_cast<char*>(NULL), 0)).Times(1).WillOnce(::testing::Return(static_cast<char*>("5")));
  // Weight Index
  function = "layer_ind";
  EXPECT_CALL(*mock, execFunc(function, static_cast<char*>(NULL), 0)).Times(1).WillOnce(::testing::Return(static_cast<char*>("5")));
  
  EXPECT_CALL(*mock, pg2i(valueStr)).Times(3)
    .WillOnce(::testing::Return(3))  // Return Value: Nodes
    .WillOnce(::testing::Return(2))  // Return Value: Inputs
    .WillOnce(::testing::Return(5)); // Return Value: Index

  function = "get_wb";
  EXPECT_CALL(*mock, execFunc(function, static_cast<char*>(NULL), 5)).Times(1).WillOnce(::testing::Return(static_cast<char*>("5.5")));
  EXPECT_CALL(*mock, execFunc(function, static_cast<char*>(NULL), 6)).Times(1).WillOnce(::testing::Return(static_cast<char*>("5.5")));
  EXPECT_CALL(*mock, execFunc(function, static_cast<char*>(NULL), 7)).Times(1).WillOnce(::testing::Return(static_cast<char*>("5.5")));
  EXPECT_CALL(*mock, execFunc(function, static_cast<char*>(NULL), 8)).Times(1).WillOnce(::testing::Return(static_cast<char*>("5.5")));
  EXPECT_CALL(*mock, execFunc(function, static_cast<char*>(NULL), 9)).Times(1).WillOnce(::testing::Return(static_cast<char*>("5.5")));
  EXPECT_CALL(*mock, execFunc(function, static_cast<char*>(NULL),10)).Times(1).WillOnce(::testing::Return(static_cast<char*>("5.5")));
  valueStr = "5.5";
  EXPECT_CALL(*mock, pg2f(valueStr)).Times(6).WillRepeatedly(::testing::Return(5.5f));

  dMatrix out = pg->getWeight();
  EXPECT_EQ(2, out.rows());
  EXPECT_EQ(3, out.cols());
  EXPECT_FLOAT_EQ(5.5, out(1, 1));
}

/*
  Test:         Bias
  Description:
    Ensure expected results using the SQL "get_wb" function
*/
TEST_F(PGLayerTest, Bias) {
  // Bias Height Config
  function = "layer_nodes";
  EXPECT_CALL(*mock, execFunc(function, static_cast<char*>(NULL), 0)).Times(1).WillOnce(::testing::Return(static_cast<char*>("5")));
  // Bias Index
  function = "layer_ind";
  EXPECT_CALL(*mock, execFunc(function, static_cast<char*>(NULL), 0)).Times(1).WillOnce(::testing::Return(static_cast<char*>("5")));

  EXPECT_CALL(*mock, pg2i(valueStr)).Times(2)
    .WillOnce(::testing::Return(2))  // Return Value: Nodes
    .WillOnce(::testing::Return(5)); // Return Value: Index

  function = "get_wb";
  EXPECT_CALL(*mock, execFunc(function, static_cast<char*>(NULL), 5)).Times(1).WillOnce(::testing::Return(static_cast<char*>("5.5")));
  EXPECT_CALL(*mock, execFunc(function, static_cast<char*>(NULL), 6)).Times(1).WillOnce(::testing::Return(static_cast<char*>("5.5")));
  valueStr = "5.5";
  EXPECT_CALL(*mock, pg2f(valueStr)).Times(2).WillRepeatedly(::testing::Return(5.5f));

  dMatrix out = pg->getBias();
  EXPECT_EQ(2, out.rows());
  EXPECT_EQ(1, out.cols());
  EXPECT_FLOAT_EQ(5.5, out(1, 0));
}

/*
  Test:         Configuration
  Description:
    Ensure expected results are formatted properly within the layer
    configuration output
*/
//TEST_F(PGLayerTest, Configuration) {
//  LayerConfiguration capture = pg->getLayer("MSFT", 1);
//
//  EXPECT_EQ(3, capture.layerWidth);
//  EXPECT_EQ(2, capture.layerHeight);
//  EXPECT_EQ(LayerTypes::FULLYCONNECTED, capture.Layer);
//  EXPECT_EQ(ActivationTypes::RELU, capture.Activation);
//
//  EXPECT_DOUBLE_EQ(capture.weight(0, 1), 3.5);
//  EXPECT_DOUBLE_EQ(capture.bias(0, 0), 7.5);
//}
