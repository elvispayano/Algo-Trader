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

#----------------------------------------------------------------------
# Configure Project Source/Header Files
#----------------------------------------------------------------------

# Library header files
set(HEADERS
 "trader.h"
 )

# Library source files
set(SRC
  "trader.cpp"
)

#----------------------------------------------------------------------
# Configure Project Interface Settings
#----------------------------------------------------------------------

# Define library requirements
add_library(main ${HEADERS} ${SRC})

# Provide dependents with header include directory
target_include_directories(main PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# Configure library properties
set_target_properties(main PROPERTIES LINKER_LANGUAGE CXX)

# Link library dependencies
target_link_libraries(main PRIVATE interfaces)
target_link_libraries(main PRIVATE neuralnetwork)
