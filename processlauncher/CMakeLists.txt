cmake_minimum_required(VERSION 3.16)

project(processlauncher LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core RemoteObjects)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core RemoteObjects)

add_executable(processlauncher
  main.cpp
  appservice.h
)
target_link_libraries(processlauncher Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::RemoteObjects)

target_include_directories(processlauncher PRIVATE build/Desktop-Debug)

qt6_add_repc_sources(processlauncher appservice.rep)

include(GNUInstallDirs)
install(TARGETS processlauncher
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
