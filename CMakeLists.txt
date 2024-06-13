cmake_minimum_required(VERSION 3.5)
project(Textual_Game)

# Set compiler flags
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)

# Add source files
file(GLOB_RECURSE SOURCES src/*)
add_executable(Textual_Game ${SOURCES})

# Link libraries
add_subdirectory(engine)
target_link_libraries(Textual_Game Engine)

# Copy resources
file(COPY assets/ DESTINATION ${CMAKE_BINARY_DIR})
