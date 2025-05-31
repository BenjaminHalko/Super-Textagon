cmake_minimum_required(VERSION 3.16)
project(Engine)

# Set C++ standard
enable_language(CXX)
set(CMAKE_CXX_STANDARD 20)

if (NOT EMSCRIPTEN)
    # Download SoLoud
    include(FetchContent)
    FetchContent_Declare(
        so_loud
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
        URL https://solhsa.com/soloud/soloud_20200207_lite.zip
    )
    FetchContent_MakeAvailable(so_loud)

    # Define SoLoud backend
    add_definitions(-DWITH_COREAUDIO)

    # Link SoLoud
    file(GLOB SO_LOUD_CORE ${so_loud_SOURCE_DIR}/src/core/*)
    file(GLOB SO_LOUD_BACKEND ${so_loud_SOURCE_DIR}/src/backend/coreaudio/*)
    file(GLOB SO_LOUD_AUDIOSOURCE ${so_loud_SOURCE_DIR}/src/audiosource/wav/*)
    add_library(so_loud
        ${SO_LOUD_CORE}
        ${SO_LOUD_BACKEND}
        ${SO_LOUD_AUDIOSOURCE}
    )
    target_include_directories(so_loud PUBLIC ${so_loud_SOURCE_DIR}/include)
endif()

# Add source files
file(GLOB_RECURSE ENGINE_SOURCES src/*)
add_library(Engine ${ENGINE_SOURCES})

# Include Dependencies
target_include_directories(Engine PUBLIC include)

if (NOT EMSCRIPTEN)
    target_link_libraries(Engine so_loud)
    
    # Link CoreGraphics framework on macOS
    if (APPLE)
        find_library(CORE_GRAPHICS CoreGraphics)
        find_library(CORE_AUDIO CoreAudio)
        find_library(AUDIO_TOOLBOX AudioToolbox)
        find_library(AUDIO_UNIT AudioUnit)
        target_link_libraries(Engine ${CORE_GRAPHICS} ${CORE_AUDIO} ${AUDIO_TOOLBOX} ${AUDIO_UNIT})
    endif()

    if (UNIX)
        # Find and link ncurses
        find_package(Curses REQUIRED)
        target_link_libraries(Engine ${CURSES_LIBRARIES})
    endif()
endif()
