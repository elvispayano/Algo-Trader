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

# Required Packages
set(BROKER_FOUND FALSE)

# PostgreSQL Package
find_package (PostgreSQL REQUIRED)

# Interactive Broker Definitions
include(FetchContent)
FetchContent_Declare(interactive_broker
  URL               "http://interactivebrokers.github.io/downloads/twsapi_macunix.976.01.zip"
  SOURCE_DIR        "${CMAKE_CURRENT_BINARY_DIR}/ib-src"
  #CONFIGURE_COMMAND "" # Disable configure step
  #BUILD_COMMAND     "" # Disable build step.
  #INSTALL_COMMAND   "" # Disable install step.
)
FetchContent_MakeAvailable(interactive_broker)

set(IB_SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/ib-src/IBJts/source/cppclient/client")
FILE(GLOB IB_SRC "${IB_SOURCE_DIR}/*.cpp")
FILE(GLOB IB_HDR "${IB_SOURCE_DIR}/*.h")
set(SRC ${SRC} ${IB_SRC})
set(HEADERS ${HEADERS} ${IB_HDR})

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

# PostgreSQL Library
if(${PostgreSQL_FOUND})
  target_include_directories(interfaces PUBLIC "${PostgreSQL_INCLUDE_DIR}")
  target_link_libraries(interfaces PRIVATE "${PostgreSQL_LIBRARY}")
endif()

target_include_directories(interfaces PUBLIC "${IB_SOURCE_DIR}")
