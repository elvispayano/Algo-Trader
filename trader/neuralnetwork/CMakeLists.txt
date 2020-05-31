# Neural Network CMake
#
# Description:
# This CMake file will generate the Neural Network library and link the appropriate libraries
#
# Library Dependencies:
# - Utilities
#
# Author: Elvis Payano

cmake_minimum_required(VERSION 3.8)

set(HEADERS
  "activation.h"
)

set(SRC
  "activation.cpp"
)

add_library(neuralnetwork ${HEADERS} ${SRC})
target_include_directories(neuralnetwork PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
set_target_properties(neuralnetwork PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(neuralnetwork PRIVATE utilities)