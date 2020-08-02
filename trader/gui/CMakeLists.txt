# Trader Main CMake
#
# Description:
# This CMake file will generate the Trader Main library and link the appropriate libraries
#
# Library Dependencies:
# - None
#
# Author: Elvis Payano

# CMake Configuration
cmake_minimum_required(VERSION 3.8)

#----------------------------------------------------------------------
# Configure Project Source/Header Files
#----------------------------------------------------------------------

if(NOT Qt5_DIR)
  message(STATUS "Default Setting for Qt5")
  set(Qt5_DIR "C:\\Qt\\5.15.0\\msvc2019_64\\lib\\cmake\\Qt5")
endif()

find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


# Library header files
set(HEADERS
  "dialog_interactivebroker.h"
  "dialog_network_create.h"
  "dialog_postgres.h"
  "window_main.h"
 )

# Library source files
set(SRC
  "dialog_interactivebroker.cpp"
  "dialog_network_create.cpp"
  "dialog_postgres.cpp"
  "window_main.cpp"
  "window_main_connections.cpp"
  "window_main_created.cpp"
  "window_main_run.cpp"
)

# Library UI files
set(UI
  "dialog_interactivebroker.ui"
  "dialog_network_create.ui"
  "dialog_postgres.ui"
  "window_main.ui"
)

qt_wrap_ui(UI_WRAPPED ${UI})
qt_wrap_cpp(MOC_WRAPPED ${HEADERS})

#----------------------------------------------------------------------
# Configure Project Interface Settings
#----------------------------------------------------------------------

# Define library requirements
add_library(gui ${HEADERS} ${SRC} ${UI_WRAPPED} ${MOC_WRAPPED})

# Provide dependents with header include directory
target_include_directories(gui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# Configure library properties
set_target_properties(gui PROPERTIES LINKER_LANGUAGE CXX)

#----------------------------------------------------------------------
# Link Libraries
#----------------------------------------------------------------------

# Link library dependencies
target_link_libraries(gui PUBLIC Qt5::Core)
target_link_libraries(gui PUBLIC Qt5::Gui)
target_link_libraries(gui PUBLIC Qt5::Widgets)

target_link_libraries(gui PUBLIC tests)
target_link_libraries(gui PUBLIC interfaces)
target_link_libraries(gui PUBLIC neuralnetwork)
target_link_libraries(gui PUBLIC utilities)
