cmake_minimum_required(VERSION 3.0)
project(QtWorkshop)

set(CMAKE_CXX_STANDARD 11)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Find the QtWidgets library
find_package(Qt5Core)
find_package(Qt5Network)

set(SOURCE_FILES main.cpp awesomeserver.cpp awesomeserver.h resources/res.qrc)

add_executable(QtWorkshop ${SOURCE_FILES})

target_link_libraries(QtWorkshop Qt5::Core Qt5::Network)