cmake_minimum_required(VERSION 3.10.0)

project(astar)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-Wall -Werror)

include_directories(include/)
include_directories(play/)

add_executable(astar main.cpp)

add_executable(play play/play.cpp)

add_executable(test test/test.cpp)