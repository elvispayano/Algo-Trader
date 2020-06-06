# Neural Network CMake
#
# Description:
# This CMake file will generate the Neural Network library and link the appropriate libraries
#
# Library Dependencies:
# - Utilities
#
# Author: Elvis Payano

# CMake requirements
cmake_minimum_required(VERSION 3.8)

# Library header files
set(HEADERS
  "activation.h"
  "fully_connected_layer.h"
  "layer_base.h"
  "neural_network.h"
)

# Library source files
set(SRC
  "activation.cpp"
  "fully_connected_layer.cpp"
  "layer_base.cpp"
  "neural_network.cpp"
)

# Define library requirements
add_library(neuralnetwork ${HEADERS} ${SRC})

# Provide dependents with header include directory
target_include_directories(neuralnetwork PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# Configure library properties
set_target_properties(neuralnetwork PROPERTIES LINKER_LANGUAGE CXX)

# Link library dependencies
target_link_libraries(neuralnetwork PRIVATE utilities)
