cmake_minimum_required(VERSION 3.10)
project(Task3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(message_type
    src/task3.cpp
    src/task3.hpp
)

target_include_directories(message_type PUBLIC src)

add_executable(task3
    src/main.cpp
)

target_link_libraries(task3 PRIVATE message_type)