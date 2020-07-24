# Interfaces CMake
#
# Description:
# This CMake file will generate the Interfaces library that will be responsible for
# communicating with external applications
#
# Library Dependencies:
# - Interactive Broker (TWS API)
# - PostgreSQL
# - Utilities
#
# Author: Elvis Payano

# CMake requirements
cmake_minimum_required(VERSION 3.8)

#----------------------------------------------------------------------
# Configure Project Source/Header Files
#----------------------------------------------------------------------

# Library header files
set(HEADERS
  "broker_base.h"
  "database_base.h"
)

# Library source files
set(SRC
  "database_base.cpp"
)

# Required Packages
set(DATABASE_FOUND FALSE)
set(BROKER_FOUND FALSE)

# PostgreSQL Package
find_package (PostgreSQL REQUIRED)
if(${PostgreSQL_FOUND})
  set(DATABASE_FOUND TRUE)
  set(HEADERS ${HEADERS} "postgres.h")
  set(SRC ${SRC} "postgres.cpp")
endif()

# Interactive Broker Definitions
set(IB_CPP_DIR "C:\\TWS API\\source\\CppClient")
if(EXISTS ${IB_CPP_DIR})
  set(BROKER_FOUND TRUE)
  set(HEADERS ${HEADERS} "ib_wrapper.h" "interactive_broker.h")
  set(SRC ${SRC} "ib_wrapper.cpp" "interactive_broker.cpp")
  set(IB_INCLUDE_DIR "${IB_CPP_DIR}\\client")
  set(IB_LIB
    "${IB_CPP_DIR}\\lib\\TwsSocketClient.lib"
    "${IB_CPP_DIR}\\${CMAKE_BUILD_TYPE}\\IB.lib"
  )
endif()

#----------------------------------------------------------------------
# Configure Project Interface Settings
#----------------------------------------------------------------------

# Define library requirements
add_library(interfaces ${HEADERS} ${SRC})

# Provide dependents with header include directory
target_include_directories(interfaces PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# Configure library properties
set_target_properties(interfaces PROPERTIES LINKER_LANGUAGE CXX)

#----------------------------------------------------------------------
# Link Libraries
#----------------------------------------------------------------------

# Link library dependencies
target_link_libraries(interfaces PRIVATE utilities)

# Library Check
if(NOT DATABASE_FOUND)
  message(FATAL_ERROR "Error: Database library not found")
endif()
if(NOT BROKER_FOUND)
  message(FATAL_ERROR "Error: Broker library not found")
endif()

# PostgreSQL Library
if(${PostgreSQL_FOUND})
  target_include_directories(interfaces PUBLIC "${PostgreSQL_INCLUDE_DIR}")
  target_link_libraries(interfaces PRIVATE "${PostgreSQL_LIBRARY}")
endif()

if(EXISTS ${IB_CPP_DIR})
  target_include_directories(interfaces PUBLIC "${IB_INCLUDE_DIR}")
  target_link_libraries(interfaces PRIVATE "${IB_LIB}")
endif()
