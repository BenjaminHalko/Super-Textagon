cmake_minimum_required(VERSION 3.5)
project(Textual_Game)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SOURCES src/*)
add_executable(Textual_Game ${SOURCES})
