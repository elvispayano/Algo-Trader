# Unit Testing CMake
#
# Description:
# This CMake file will generate the GTest Unit Test library and link the appropriate libraries
#
# Library Dependencies:
# - Utilities
# - Neural Network
# - GTest (External)
#
# Author: Elvis Payano

# CMake requirements
cmake_minimum_required(VERSION 3.8)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Library header files
set(HEADERS
  "test_main.h"
)

# Library source files
set(SRC
  "test_main.cpp"
  "test_activation.cc"
  "test_database_base.cc"
  "test_interactive_broker.cc"
  "test_layer_base.cc"
  "test_matrix.cc"
  "test_neural_network.cc"
  "test_stock.cc"
  "test_trader.cc"
  "test_utl_math.cc"
)

# Define library requirements
add_library(tests OBJECT ${HEADERS} ${SRC})

# Provide dependents with header include directory
target_include_directories(tests PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# Configure library properties
set_target_properties(tests PROPERTIES LINKER_LANGUAGE CXX)

# Link library dependencies
target_link_libraries(tests PRIVATE gtest_main)
target_link_libraries(tests PRIVATE gmock_main)
target_link_libraries(tests PRIVATE utilities)
target_link_libraries(tests PRIVATE neuralnetwork)
target_link_libraries(tests PRIVATE interfaces)
target_link_libraries(tests PRIVATE main)
