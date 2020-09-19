# Project Main CMake
#
# Author: Elvis Payano

cmake_minimum_required(VERSION 3.8)

set(ALGO_TRADER_VERSION 0.0.1)
project(algorithmic-trader VERSION ${ALGO_TRADER_VERSION} LANGUAGES CXX C)

enable_testing()
include(cmake/gtest.cmake)

add_subdirectory(gui)
add_subdirectory(interfaces)
add_subdirectory(neuralnetwork)
add_subdirectory(utilities)