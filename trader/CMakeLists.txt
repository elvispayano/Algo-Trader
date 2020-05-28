# CMakeList.txt : CMake project for trader, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project (trader)

add_subdirectory(util)
add_subdirectory(trader)
add_subdirectory(tests)


# Now simply link against gtest or gtest_main as needed. Eg
# Add source to this project's executable.
add_executable (${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} PRIVATE main)
target_link_libraries(${PROJECT_NAME} PRIVATE util)