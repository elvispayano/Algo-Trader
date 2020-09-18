# Interfaces CMake
#
# Description:
# CMake build script for interfaces
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
project(interfaces VERSION ${ALGO_TRADER_VERSION} LANGUAGES CXX C)
cmake_minimum_required(VERSION 3.8)

#----------------------------------------------------------------------
# External Interfaces
#----------------------------------------------------------------------

# Broker API
include(cmake/broker.cmake)

# Database API
find_package(PostgreSQL REQUIRED)

#----------------------------------------------------------------------
# Build
#----------------------------------------------------------------------
set(INTERFACES_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories(${INTERFACES_INCLUDE_DIRS})

set(INTERFACE_SRC
  "src/database_base.cpp"
  "src/ib_wrapper.cpp"
  "src/interactive_broker.cpp"
  "src/postgres.cpp"
)

add_library(interfaces ${INTERFACE_SRC})
target_include_directories(interfaces SYSTEM INTERFACE "$<BUILD_INTERFACE:${INTERFACES_INCLUDE_DIRS}>")

# Link Libraries
target_link_libraries(interfaces PRIVATE broker)
target_link_libraries(interfaces PRIVATE utilities)

# Postgres
if(${PostgreSQL_FOUND})
  target_include_directories(interfaces PUBLIC "${PostgreSQL_INCLUDE_DIR}")
  target_link_libraries(interfaces PRIVATE "${PostgreSQL_LIBRARY}")
endif()

target_include_directories(interfaces PUBLIC "${IB_SOURCE_DIR}")

#----------------------------------------------------------------------
# Samples
#----------------------------------------------------------------------
if(BUILD_SAMPLES)
  cxx_sample(interactive_broker interfaces utilities)
endif()

#----------------------------------------------------------------------
# Testing
#----------------------------------------------------------------------
if(BUILD_TESTS)
  cxx_test(database_base      interfaces utilities gtest_main gmock)
  cxx_test(interactive_broker interfaces utilities gtest_main gmock)
endif()
