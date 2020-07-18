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
project(trader)

# Project build directories
add_subdirectory(util)
add_subdirectory(interfaces)
add_subdirectory(trader)
add_subdirectory(neuralnetwork)
add_subdirectory(tests)

# Executable definition
add_executable (${PROJECT_NAME} "main.cpp" "main.h")

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE main)
target_link_libraries(${PROJECT_NAME} PRIVATE interfaces)
target_link_libraries(${PROJECT_NAME} PRIVATE neuralnetwork)
target_link_libraries(${PROJECT_NAME} PRIVATE tests)
