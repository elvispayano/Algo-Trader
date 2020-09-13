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
set(UTIL_TEST_SRC
  "tests/matrix.cc"
  "tests/stock.cc"
  "tests/utl_math.cc"
)

add_executable(utilities_test ${UTIL_TEST_SRC})
target_link_libraries(utilities_test PRIVATE utilities gtest_main)
target_link_directories(utilities_test PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
add_test(NAME utilities_test COMMAND "$<TARGET_FILE:utilities_test>")
