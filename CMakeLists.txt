cmake_minimum_required(VERSION 3.5)
project(Super_Textagon)

# Set compiler flags
enable_language(CXX)
set(CMAKE_CXX_STANDARD 20)

# Add source files
file(GLOB_RECURSE SOURCES src/*)
add_executable(Super_Textagon ${SOURCES})

# Link libraries
add_subdirectory(engine)
target_link_libraries(Super_Textagon Engine)

# Copy assets
set_target_properties(Super_Textagon PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(COPY assets/audio DESTINATION ${CMAKE_BINARY_DIR}/bin)
if (NOT EMSCRIPTEN)
    file(COPY assets/icon.ico DESTINATION ${CMAKE_BINARY_DIR})
else()
    file(COPY assets/web/ DESTINATION ${CMAKE_BINARY_DIR}/bin)
    file(COPY assets/icon.ico DESTINATION ${CMAKE_BINARY_DIR}/bin)
endif()

# Set Emscripten flags
if (EMSCRIPTEN)
    set_target_properties(Super_Textagon PROPERTIES LINK_FLAGS "-sEXPORTED_FUNCTIONS=\"['_main', '_malloc', '_free']\" --preload-file ${CMAKE_BINARY_DIR}/bin/audio/")
endif()
