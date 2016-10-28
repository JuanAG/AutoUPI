cmake_minimum_required(VERSION 3.6)
project(AutoUPI)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES HelloWorld.cpp)
add_executable(AutoUPI ${SOURCE_FILES})