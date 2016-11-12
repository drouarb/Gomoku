enable_testing()

FILE(
        GLOB_RECURSE
        GOMOKU_TESTS
        src/*.cpp
)

include_directories(include)

foreach(test ${GOMOKU_TESTS_SOURCES})
    get_filename_component(test_name ${test} NAME_WE)
    add_executable(${test_name} ${test})
    add_test(${test_name} ${test_name})
endforeach(test)
