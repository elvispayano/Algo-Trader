if(WIN32)
  if(NOT Qt5_DIR)
    set(Qt5_DIR "C:\\Qt\\5.15.0\\msvc2019_64\\lib\\cmake\\Qt5")
  endif()
else()
  set(QT_UIC_EXECUTABLE "/usr/bin/uic-qt5")
endif()

find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets)
set(CMAKE_INCLUDE_CURRENT_DIR ON)