cmake_minimum_required(VERSION 3.16)
project(BallGame VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(DIR_SRC src)
set(DIR_ENGINE ${DIR_SRC}/engine)
set(DIR_CONFIG ${DIR_SRC}/config)

set(SOURCES
    ${DIR_CONFIG}/gameconfig.cpp
    ${DIR_ENGINE}/Board.cpp
    ${DIR_ENGINE}/Ball.cpp
    ${DIR_ENGINE}/SoundManager.cpp
    ${DIR_ENGINE}/GameState.cpp
    ${DIR_ENGINE}/Game.cpp
    ${DIR_SRC}/main.cpp 
)

add_executable(BallGame ${SOURCES})

target_compile_options(BallGame PRIVATE -Wall -Wextra -Wpedantic)
target_compile_options(BallGame PRIVATE -Werror)

target_link_libraries(BallGame sfml-system sfml-window sfml-graphics sfml-audio)