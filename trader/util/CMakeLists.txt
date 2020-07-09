# Utilities CMake
#
# Description:
# This CMake file will generate the Utilities library.
#
# Library Dependencies:
# - None
#
# Author: Elvis Payano

cmake_minimum_required(VERSION 3.8)

set(HEADERS
  "utl_math.h"
  "matrix.h"
  "network_types.h"
  "stock.h"
  )

set(SRC
  "stock.cpp"
  "utl_math.cpp"
)

add_library(utilities ${HEADERS} ${SRC})
target_include_directories(utilities PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
set_target_properties(utilities PROPERTIES LINKER_LANGUAGE CXX)