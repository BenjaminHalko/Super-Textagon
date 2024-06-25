cmake_minimum_required(VERSION 3.5)
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
    add_definitions(-DWITH_MINIAUDIO)

    # Link SoLoud
    file(GLOB SO_LOUD_CORE ${so_loud_SOURCE_DIR}/src/core/*)
    file(GLOB SO_LOUD_BACKEND ${so_loud_SOURCE_DIR}/src/backend/miniaudio/*)
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
    # Link Ncurses
    if (UNIX)
        find_package(Curses REQUIRED)
        target_link_libraries(Engine PUBLIC ${CURSES_LIBRARIES} so_loud)
        target_include_directories(Engine PUBLIC ${CURSES_INCLUDE_DIR})
    else()
        target_link_libraries(Engine so_loud)
    endif()
endif()
