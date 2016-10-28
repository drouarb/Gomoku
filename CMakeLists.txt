cmake_minimum_required(VERSION 3.6)
project(Gomoku)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
FILE(
        GLOB_RECURSE
        GOMOKU
        src/*.cpp
        src/Core/*.cpp
        src/Gui/*.cpp
        src/Players/*.cpp
)

include_directories(include)
include(include/Core)
include(include/Players)
include(include/Gui)
add_executable(Gomoku)