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

cmake_minimum_required (VERSION 3.8)
project (trader)

add_subdirectory(util)
add_subdirectory(trader)
add_subdirectory(neuralnetwork)
add_subdirectory(tests)


# Now simply link against gtest or gtest_main as needed. Eg
# Add source to this project's executable.
add_executable (${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} PRIVATE main)
target_link_libraries(${PROJECT_NAME} PRIVATE tests)

add_compile_definitions("DEBUG")

add_test(NAME MatrixTest COMMAND tests)