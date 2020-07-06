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

# TWS API Definitions
set(IB_INCLUDE_DIR "C:\\TWS API\\source\\CppClient\\client")
set(IB_LIB
  "C:\\TWS API\\source\\CppClient\\lib\\TwsSocketClient.lib"
  "C:\\TWS API\\source\\CppClient\\Debug\\IB.lib"
)

# Library header files
set(HEADERS
  "broker_base.h"
  "database_base.h"
  "ib_wrapper.h"
  "interactive_broker.h"
  "postgres.h"
)

# Library source files
set(SRC
  "database_base.cpp"
  "ib_wrapper.cpp"
  "interactive_broker.cpp"
  "postgres.cpp"
)

# Define library requirements
add_library(interfaces ${HEADERS} ${SRC})

# Provide dependents with header include directory
target_include_directories(interfaces PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(interfaces PUBLIC "${PostgreSQL_INCLUDE_DIR}")
target_include_directories(interfaces PUBLIC "${IB_INCLUDE_DIR}")

# Configure library properties
set_target_properties(interfaces PROPERTIES LINKER_LANGUAGE CXX)

# Link library dependencies
target_link_libraries(interfaces PRIVATE utilities)
target_link_libraries(interfaces PRIVATE "${PostgreSQL_LIBRARY}")
target_link_libraries(interfaces PRIVATE "${IB_LIB}")
