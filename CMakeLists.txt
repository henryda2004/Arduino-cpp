cmake_minimum_required(VERSION 3.24)
project(Estesirve)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5SerialPort)

add_executable(Estesirve main.cpp mainWindow.cpp mainWindow.cpp mainWindow.h mainWindow.ui)

target_link_libraries(Estesirve
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::SerialPort
        pthread
        )

