cmake_minimum_required(VERSION 3.5)
project(Super_Textagon)

# Set compiler flags
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)

# Add source files
file(GLOB_RECURSE SOURCES src/*)
add_executable(Super_Textagon ${SOURCES})

# Link libraries
add_subdirectory(engine)
target_link_libraries(Super_Textagon Engine)

# Copy resources
file(COPY assets/ DESTINATION ${CMAKE_BINARY_DIR})
