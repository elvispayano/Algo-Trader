# Trader Main CMake
#
# Description:
# This CMake file will generate the Trader Main library and link the appropriate libraries
#
# Library Dependencies:
# - None
#
# Author: Elvis Payano

# CMake requirements
cmake_minimum_required(VERSION 3.8)

# Library header files
set(HEADERS

)

# Library source files
set(SRC
  "trader.cpp"
)

# Define library requirements
add_library(main ${HEADERS} ${SRC})

# Provide dependents with header include directory
target_include_directories(main PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# Configure library properties
set_target_properties(main PROPERTIES LINKER_LANGUAGE CXX)
