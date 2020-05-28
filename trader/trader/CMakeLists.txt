# Main Header
cmake_minimum_required(VERSION 3.8)

set(HEADERS

)

set(SRC
  "trader.cpp"
)

add_library(main ${HEADERS} ${SRC})
target_include_directories(main PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")