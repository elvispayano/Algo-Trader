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

if(BUILD_TESTS)
  include(${CMAKE_SOURCE_DIR}/cmake/gtest.cmake)
  enable_testing()
endif()

#----------------------------------------------------------------------
# Project Settings
#----------------------------------------------------------------------
set(ALGO_TRADER_VERSION 0.0.1)
set(ALGO_TRADER_MIN_CMAKE 3.8)
project(algorithmic-trader LANGUAGES CXX C)
cmake_minimum_required(VERSION 3.8)

#----------------------------------------------------------------------
# External Interfaces
#----------------------------------------------------------------------

# Broker API
include(${CMAKE_SOURCE_DIR}/cmake/broker.cmake)

# Database API
find_package(PostgreSQL REQUIRED)

#----------------------------------------------------------------------
# Build Libraries
#----------------------------------------------------------------------
add_subdirectory(comms)
add_subdirectory(neuralnetwork)
add_subdirectory(utilities)

#----------------------------------------------------------------------
# Build
#----------------------------------------------------------------------
set(ALGO_TRADER_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories(${ALGO_TRADER_INCLUDE_DIRS})

set(ALGO_TRADER_SRC
  "src/broker_controller.cpp"
  "src/database_base.cpp"
  "src/database_controller.cpp"
  "src/data_server.cpp"
  "src/ib_wrapper.cpp"
  "src/interactive_broker.cpp"
  "src/postgres.cpp"
  "src/trader_controller.cpp"
  "src/main.cpp"
)

add_executable(algorithmic-trader ${ALGO_TRADER_SRC})

target_include_directories(algorithmic-trader SYSTEM INTERFACE "$<BUILD_INTERFACE:${ALGO_TRADER_INCLUDE_DIRS}>")
target_include_directories(algorithmic-trader PRIVATE "${PostgreSQL_INCLUDE_DIR}")
target_include_directories(algorithmic-trader PRIVATE "${IB_SOURCE_DIR}")

target_link_libraries(algorithmic-trader PRIVATE broker)
target_link_libraries(algorithmic-trader PRIVATE comms)
target_link_libraries(algorithmic-trader PRIVATE neuralnetwork)
target_link_libraries(algorithmic-trader PRIVATE utilities)
target_link_libraries(algorithmic-trader PRIVATE "${PostgreSQL_LIBRARY}")

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
