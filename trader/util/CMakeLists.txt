# Utilities CMake
#
# Description:
# This CMake file will generate the Utilities library.
#
# Library Dependencies:
# - None
#
# Author: Elvis Payano

# CMake requirements
cmake_minimum_required(VERSION 3.8)

#----------------------------------------------------------------------
# Configure Project Source/Header Files
#----------------------------------------------------------------------

set(HEADERS
  "broker_types.h"
  "matrix.h"
  "network_types.h"
  "stock.h"
  "utl_math.h"
  )

set(SRC
  "stock.cpp"
  "utl_math.cpp"
)

#----------------------------------------------------------------------
# Configure Project Interface Settings
#----------------------------------------------------------------------

# Define library requirements
add_library(utilities ${HEADERS} ${SRC})

# Provide dependents with header include directory
target_include_directories(utilities PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# Configure library properties
set_target_properties(utilities PROPERTIES LINKER_LANGUAGE CXX)
