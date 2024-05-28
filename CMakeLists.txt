cmake_minimum_required(VERSION 3.16)
project(BallGame VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(BallGame src/main.cpp)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(BallGame PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(BallGame PRIVATE -Werror)
endif()

target_link_libraries(BallGame sfml-system sfml-window sfml-graphics sfml-audio)