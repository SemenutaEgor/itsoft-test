# Подтягиваем GoogleTest
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(run_tests
    tests_task2.cpp
    ../src/task2.cpp
)

target_include_directories(run_tests PRIVATE ../src)

target_link_libraries(run_tests
    gtest
    gtest_main
)

add_test(NAME Task2Tests COMMAND run_tests)
