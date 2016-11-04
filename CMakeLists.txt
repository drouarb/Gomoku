cmake_minimum_required(VERSION 3.0)
project(Gomoku)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
FILE(
        GLOB_RECURSE
        GOMOKU
        src/*.cpp
        src/Core/*.cpp
        src/Gui/*.cpp
        src/Players/*.cpp
        include/*.hh
)

include_directories(include)
include_directories(include/Core)
include_directories(include/Players)
include_directories(include/Gui)
add_executable(Gomoku ${GOMOKU})
target_link_libraries(Gomoku  -lSDL2 -lSDL2_image -lSDL2_ttf -lpthread)
