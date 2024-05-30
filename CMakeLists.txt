cmake_minimum_required(VERSION 3.28)
project(Textual_Game)

set(CMAKE_CXX_STANDARD 11)

glob_recursive(Textual_Game SOURCES src*/)
add_executable(Textual_Game ${SOURCES})
