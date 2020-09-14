# Utilities CMake
#
# Description:
# CMake build script for Utilities
#
# Author: Elvis Payano

#----------------------------------------------------------------------
# Options
#----------------------------------------------------------------------

#----------------------------------------------------------------------
# Settings
#----------------------------------------------------------------------
project(utilities CXX)
set(PROJECT_VERSION ${ALGO_TRADER_VERSION})
cmake_minimum_required(VERSION 3.8)

#----------------------------------------------------------------------
# Build
#----------------------------------------------------------------------
set(UTILITIES_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories(${UTILITIES_INCLUDE_DIRS})

set(UTIL_SRC
  "src/random_number.cpp"
  "src/stock.cpp"
  "src/utl_math.cpp"
)

add_library(utilities ${UTIL_SRC})
target_include_directories(utilities SYSTEM INTERFACE "$<BUILD_INTERFACE:${UTILITIES_INCLUDE_DIRS}>")

#----------------------------------------------------------------------
# Testing
#----------------------------------------------------------------------
include(${CMAKE_SOURCE_DIR}/cmake/internal_functions.cmake)

cxx_test(matrix   utilities gtest_main)
cxx_test(stock    utilities gtest_main)
cxx_test(utl_math utilities gtest_main)
