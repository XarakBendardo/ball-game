cmake_minimum_required(VERSION 3.16)
project(BallGame VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES 
    src/engine/Board.cpp
    src/engine/Ball.cpp
    src/engine/Game.cpp
    src/main.cpp 
)

add_executable(BallGame ${SOURCES})

target_compile_options(BallGame PRIVATE -Wall -Wextra -Wpedantic)
target_compile_options(BallGame PRIVATE -Werror)

target_link_libraries(BallGame sfml-system sfml-window sfml-graphics sfml-audio)