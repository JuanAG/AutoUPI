cmake_minimum_required(VERSION 3.6)
project(AutoUPI)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES HelloWorld.cpp)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)

add_executable(AutoUPI ${SOURCE_FILES})

target_link_libraries(AutoUPI Qt5::Core Qt5::Widgets Qt5::Gui)