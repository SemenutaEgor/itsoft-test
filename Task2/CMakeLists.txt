cmake_minimum_required(VERSION 3.10)
project(Task2)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_subdirectory(tests)

add_executable(task2
    src/main.cpp
    src/task2.cpp
)

target_include_directories(task2 PRIVATE src)
