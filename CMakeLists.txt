# Project Main CMake
#
# Description:
# CMake build script for the Algo-Trader Project
#
# Author: Elvis Payano

#----------------------------------------------------------------------
# Options
#----------------------------------------------------------------------
option(BUILD_SAMPLES "Build Algo-Trader's sample programs" OFF)
option(BUILD_TESTS   "Build Algo-Trader's test programs"   OFF)

include(${CMAKE_SOURCE_DIR}/cmake/internal_functions.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/gtest.cmake)
enable_testing()

#----------------------------------------------------------------------
# Project Settings
#----------------------------------------------------------------------
set(ALGO_TRADER_VERSION 0.0.1)
set(ALGO_TRADER_MIN_CMAKE 3.8)
project(algorithmic-trader LANGUAGES CXX C)
cmake_minimum_required(VERSION 3.8)

#----------------------------------------------------------------------
# Build Libraries
#----------------------------------------------------------------------
add_subdirectory(comms)
add_subdirectory(interfaces)
add_subdirectory(neuralnetwork)
add_subdirectory(utilities)

#----------------------------------------------------------------------
# Build
#----------------------------------------------------------------------
set(ALGO_TRADER_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories(${ALGO_TRADER_INCLUDE_DIRS})

set(ALGO_TRADER_SRC
  "src/trader_controller.cpp"
  "src/main.cpp"
)

add_executable(algorithmic-trader ${ALGO_TRADER_SRC})
target_include_directories(algorithmic-trader SYSTEM INTERFACE "$<BUILD_INTERFACE:${ALGO_TRADER_INCLUDE_DIRS}>")

target_link_libraries(algorithmic-trader PRIVATE comms)
target_link_libraries(algorithmic-trader PRIVATE interfaces)
target_link_libraries(algorithmic-trader PRIVATE neuralnetwork)
target_link_libraries(algorithmic-trader PRIVATE utilities)

#----------------------------------------------------------------------
# Samples
#----------------------------------------------------------------------
if(BUILD_SAMPLES)
  
endif()

#----------------------------------------------------------------------
# Testing
#----------------------------------------------------------------------
if(BUILD_TESTS)
  
endif()
