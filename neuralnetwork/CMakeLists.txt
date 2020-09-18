# Neural Network CMake
#
# Description:
# CMake build script for Neural Network
#
# Author: Elvis Payano

#----------------------------------------------------------------------
# Options
#----------------------------------------------------------------------
option(BUILD_SAMPLES "Build Algo-Trader's sample programs" OFF)
option(BUILD_TESTS   "Build Algo-Trader's test programs"   OFF)

include(${CMAKE_SOURCE_DIR}/cmake/internal_functions.cmake)

#----------------------------------------------------------------------
# Settings
#----------------------------------------------------------------------
project(neuralnetwork VERSION ${ALGO_TRADER_VERSION} LANGUAGES CXX C)
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
# Samples
#----------------------------------------------------------------------
if(BUILD_SAMPLES)
  cxx_sample(neural_network neuralnetwork utilities)
endif()

#----------------------------------------------------------------------
# Testing
#----------------------------------------------------------------------
if(BUILD_TESTS)
  cxx_test(activation            neuralnetwork utilities gtest_main)
  cxx_test(fully_connected_layer neuralnetwork utilities gtest_main)
  cxx_test(layer_base            neuralnetwork utilities gtest_main gmock)
  cxx_test(neural_network        neuralnetwork utilities gtest_main)
endif()
