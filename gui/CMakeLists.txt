# Interfaces CMake
#
# Description:
# CMake build script for interfaces
#
# Author: Elvis Payano

#----------------------------------------------------------------------
# Options
#----------------------------------------------------------------------

#----------------------------------------------------------------------
# Settings
#----------------------------------------------------------------------
project(gui CXX)
set(PROJECT_VERSION ${ALGO_TRADER_VERSION})
cmake_minimum_required(VERSION 3.8)

#----------------------------------------------------------------------
# External Interfaces
#----------------------------------------------------------------------

# Qt5 API
include(cmake/qt.cmake)

#----------------------------------------------------------------------
# Build
#----------------------------------------------------------------------
set(GUI_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories(${GUI_INCLUDE_DIRS})

# Library header files
set(HEADERS
  "src/dialog_interactivebroker.h"
  "src/dialog_network_create.h"
  "src/dialog_postgres.h"
  "src/window_main.h"
 )

# Library source files
set(SRC
  "src/dialog_interactivebroker.cpp"
  "src/dialog_network_create.cpp"
  "src/dialog_postgres.cpp"
  "src/window_main.cpp"
  "src/window_main_connections.cpp"
  "src/window_main_run.cpp"
)

# Library UI files
set(UI
  "src/dialog_interactivebroker.ui"
  "src/dialog_network_create.ui"
  "src/dialog_postgres.ui"
  "src/window_main.ui"
)

qt5_wrap_ui(UI_WRAPPED ${UI})
qt5_wrap_cpp(MOC_WRAPPED ${HEADERS})

# Define library requirements
add_library(gui ${SRC} ${UI_WRAPPED} ${MOC_WRAPPED})
target_include_directories(gui SYSTEM INTERFACE "$<BUILD_INTERFACE:${INTERFACES_INCLUDE_DIRS}>")

target_link_libraries(gui PRIVATE utilities)
target_link_libraries(gui PUBLIC Qt5::Core)
target_link_libraries(gui PUBLIC Qt5::Gui)
target_link_libraries(gui PUBLIC Qt5::Widgets)

target_link_libraries(gui PUBLIC interfaces)
target_link_libraries(gui PUBLIC neuralnetwork)
target_link_libraries(gui PUBLIC utilities)