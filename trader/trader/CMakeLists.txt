# Trader Main CMake
#
# Description:
# This CMake file will generate the Trader Main library and link the appropriate libraries
#
# Library Dependencies:
# - None
#
# Author: Elvis Payano

cmake_minimum_required(VERSION 3.8)

set(HEADERS

)

set(SRC
  "trader.cpp"
)

add_library(main ${HEADERS} ${SRC})
target_include_directories(main PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")