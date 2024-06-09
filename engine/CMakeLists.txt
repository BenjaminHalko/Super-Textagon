cmake_minimum_required(VERSION 3.5)
project(Engine)

# Set C++ standard
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)

# Add source files
file(GLOB_RECURSE ENGINE_SOURCES src/*)
add_library(Engine ${ENGINE_SOURCES})

# Set include directory
target_include_directories(Engine PUBLIC include)
