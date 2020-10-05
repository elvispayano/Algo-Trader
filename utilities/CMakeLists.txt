# Utilities CMake
#
# Description:
# CMake build script for Utilities
#
# Author: Elvis Payano

#----------------------------------------------------------------------
# Options
#----------------------------------------------------------------------
option(BUILD_SAMPLES "Build Algo-Trader's sample programs" OFF)
option(BUILD_TESTS   "Build Algo-Trader's test programs"   OFF)

include(${CMAKE_SOURCE_DIR}/cmake/internal_functions.cmake)

#----------------------------------------------------------------------
# Project Settings
#----------------------------------------------------------------------
project(utilities VERSION ${ALGO_TRADER_VERSION} LANGUAGES CXX C)
cmake_minimum_required(VERSION ${ALGO_TRADER_MIN_CMAKE})

#----------------------------------------------------------------------
# Build
#----------------------------------------------------------------------
set(UTILITIES_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories(${UTILITIES_INCLUDE_DIRS})

set(UTIL_SRC
  "src/delimited_io.cpp"
  "src/matrix.cpp"
  "src/random_number.cpp"
  "src/stock.cpp"
  "src/utl_math.cpp"
)

add_library(utilities ${UTIL_SRC})
target_include_directories(utilities SYSTEM INTERFACE "$<BUILD_INTERFACE:${UTILITIES_INCLUDE_DIRS}>")

#----------------------------------------------------------------------
# Samples
#----------------------------------------------------------------------
if(BUILD_SAMPLES)
  
endif()

#----------------------------------------------------------------------
# Testing
#----------------------------------------------------------------------
if(BUILD_TESTS)
  cxx_test(matrix      utilities gtest_main gmock)
  cxx_test(stock       utilities gtest_main)
  cxx_test(utl_math    utilities gtest_main)
endif()
