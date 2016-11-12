cmake_minimum_required(VERSION 3.0)
project(Gomoku)

enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ${DBG}")
FILE(
        GLOB_RECURSE
        GOMOKU
        src/Core/*.cpp
        src/Gui/*.cpp
        src/Players/*.cpp
        include/*.hh
        tests/src/*.cpp
        tests/include/*.hh
)


include_directories(include)
include_directories(include/Core)
include_directories(tests/include)
include_directories(include/Players)
include_directories(include/Gui)
add_executable(Gomoku ${GOMOKU} src/main.cpp)
add_executable(Gomoku_tests ${GOMOKU} tests/main.cpp)
target_link_libraries(Gomoku  -lSDL2 -lSDL2_image -lSDL2_ttf -lpthread)
target_link_libraries(Gomoku_tests  -lSDL2 -lSDL2_image -lSDL2_ttf -lpthread)

FILE(
        GLOB_RECURSE
        GOMOKU_TESTS_SOURCES
        generated/*.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

foreach(test ${GOMOKU_TESTS_SOURCES})
    get_filename_component(test_name ${test} NAME_WE)
    add_executable(${test_name} ${test} ${GOMOKU})
    add_test(${test_name} ${test_name})
    target_link_libraries(${test_name}  -lSDL2 -lSDL2_image -lSDL2_ttf -lpthread)
endforeach(test)
