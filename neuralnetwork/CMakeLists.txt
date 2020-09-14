# Neural Network CMake
#
# Description:
# CMake build script for Neural Network
#
# Author: Elvis Payano

#----------------------------------------------------------------------
# Options
#----------------------------------------------------------------------

#----------------------------------------------------------------------
# Settings
#----------------------------------------------------------------------
project(neuralnetwork CXX)
set(PROJECT_VERSION ${ALGO_TRADER_VERSION})
cmake_minimum_required(VERSION 3.8)

#----------------------------------------------------------------------
# Build
#----------------------------------------------------------------------
set(NEURALNETWORK_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories(${NEURALNETWORK_INCLUDE_DIRS})

set(NN_SRC
  "src/activation.cpp"
  "src/fully_connected_layer.cpp"
  "src/layer_base.cpp"
  "src/neural_network.cpp"
)

add_library(neuralnetwork ${NN_SRC})
target_include_directories(neuralnetwork SYSTEM INTERFACE "$<BUILD_INTERFACE:${NEURALNETWORK_INCLUDE_DIRS}>")

# Link Libraries
target_link_libraries(neuralnetwork PRIVATE utilities)

#----------------------------------------------------------------------
# Testing
#----------------------------------------------------------------------
include(${CMAKE_SOURCE_DIR}/cmake/internal_functions.cmake)

cxx_test(activation            neuralnetwork utilities gtest_main)
cxx_test(fully_connected_layer neuralnetwork utilities gtest_main)
cxx_test(layer_base            neuralnetwork utilities gtest_main gmock)
cxx_test(neural_network        neuralnetwork utilities gtest_main)
