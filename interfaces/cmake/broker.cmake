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

add_library(broker ${IB_SRC})