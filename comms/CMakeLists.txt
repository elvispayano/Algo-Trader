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
project(comms VERSION ${ALGO_TRADER_VERSION} LANGUAGES CXX C)
cmake_minimum_required(VERSION ${ALGO_TRADER_MIN_CMAKE})

#----------------------------------------------------------------------
# Build
#----------------------------------------------------------------------
set(COMMS_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories(${COMMS_INCLUDE_DIRS})

set(COMMS_SRC
  "src/broker_request_update_msg.cpp"
  "src/fc_layer_msg.cpp"
)

add_library(comms ${COMMS_SRC})
target_include_directories(comms SYSTEM INTERFACE "$<BUILD_INTERFACE:${COMMS_INCLUDE_DIRS}>")

target_link_libraries(comms PRIVATE utilities)

#----------------------------------------------------------------------
# Samples
#----------------------------------------------------------------------
if(BUILD_SAMPLES)
  
endif()

#----------------------------------------------------------------------
# Testing
#----------------------------------------------------------------------
if(BUILD_TESTS)
  cxx_test(fc_layer_msg comms utilities gtest_main) 
endif()
