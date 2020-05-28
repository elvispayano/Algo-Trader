# Utilities Header
cmake_minimum_required(VERSION 3.8)

set(HEADERS
  "matrix.h"
)

set(SRC
  "temp.cpp"
)

add_library(util ${HEADERS} ${SRC})
target_include_directories(util PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
set_target_properties(util PROPERTIES LINKER_LANGUAGE CXX)