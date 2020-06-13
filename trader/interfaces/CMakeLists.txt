# Interfaces CMake
#
# Description:
# This CMake file will generate the Interfaces library that will be responsible for
# communicating with external applications
#
# Library Dependencies:
# - Utilities
#
# Author: Elvis Payano

# CMake requirements
cmake_minimum_required(VERSION 3.8)

find_package (PostgreSQL REQUIRED)

# Library header files
set(HEADERS
  "pg_connect.h"
  "pg_layer.h"
  "pg_network.h"
)

# Library source files
set(SRC
  "pg_connect.cpp"
  "pg_layer.cpp"
  "pg_network.cpp"
)

# Define library requirements
add_library(interfaces ${HEADERS} ${SRC})

# Provide dependents with header include directory
target_include_directories(interfaces PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(interfaces PUBLIC "${PostgreSQL_INCLUDE_DIR}")

# Configure library properties
set_target_properties(interfaces PROPERTIES LINKER_LANGUAGE CXX)

# Link library dependencies
target_link_libraries(interfaces PRIVATE utilities)
target_link_libraries(interfaces PRIVATE "${PostgreSQL_LIBRARY}")
