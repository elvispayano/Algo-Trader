# Project Main CMake
#
# Author: Elvis Payano

cmake_minimum_required(VERSION 3.8)

project(algorithmic-trader)
set(ALGO_TRADER_VERSION 0.0.1)

enable_testing()
include(cmake/gtest.cmake)

add_subdirectory(interfaces)
add_subdirectory(utilities)