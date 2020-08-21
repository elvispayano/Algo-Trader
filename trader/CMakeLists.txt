# Main CMake
#
# Description:
# This CMake file will generate link all libraries and generate the runtime executable
#
# Library Dependencies:
# - Trader Main
# - Tests
#
# Author: Elvis Payano

# CMake requirements
cmake_minimum_required (VERSION 3.8)

# Project description 
project(algo-trader VERSION 0.20.08)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

# Project build directories
add_subdirectory(util)
add_subdirectory(interfaces)
add_subdirectory(trader)
add_subdirectory(neuralnetwork)
add_subdirectory(tests)
#add_subdirectory(gui)

# Executable definition
add_executable (${PROJECT_NAME} "main.cpp" "main.h")

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE main)
target_link_libraries(${PROJECT_NAME} PRIVATE interfaces)
target_link_libraries(${PROJECT_NAME} PRIVATE neuralnetwork)
target_link_libraries(${PROJECT_NAME} PRIVATE tests)
#target_link_libraries(${PROJECT_NAME} PRIVATE gui)
target_link_libraries(${PROJECT_NAME} PRIVATE utilities)

# For pipeline execution
if(CI)
  add_compile_definitions(CI)
  enable_testing()
endif()
