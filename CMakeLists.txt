cmake_minimum_required(VERSION 2.8)
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
        src/helpers/*.cpp
        tests/src/*.cpp
        tests/include/*.hh
)

FILE(
        GLOB_RECURSE
        TEST_INTEPRETOR
        testIntepretor/src/*.cpp
        testIntepretor/include/*.hh
        )

include_directories(include)
include_directories(include/Core)
include_directories(tests/include)
include_directories(include/Players)
include_directories(include/Gui)
include_directories(testIntepretor/include)


add_library(Gomoku_core ${GOMOKU})

add_executable(Gomoku src/main.cpp)
add_executable(Gomoku_tests ${GOMOKU} tests/main.cpp)
add_executable(intepretor ${TEST_INTEPRETOR})
target_link_libraries(Gomoku Gomoku_core)
target_link_libraries(Gomoku_core -lSDL2 -lSDL2_image -lSDL2_ttf -lpthread)
target_link_libraries(Gomoku_tests -lSDL2 -lSDL2_image -lSDL2_ttf -lpthread Gomoku_core)

FILE(
        GLOB_RECURSE
        GOMOKU_TESTS_SOURCES
        generated/*.cpp
)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

#message("to test :" "${GOMOKU_TESTS_SOURCES}")

foreach (test ${GOMOKU_TESTS_SOURCES})
    get_filename_component(test_name ${test} NAME_WE)
    add_executable(${test_name} ${test})
    add_test(${test_name} ${test_name})
    target_link_libraries(${test_name} Gomoku_core)
endforeach (test)
