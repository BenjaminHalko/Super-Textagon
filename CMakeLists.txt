cmake_minimum_required(VERSION 3.5)
project(Textual_Game)

set(CMAKE_CXX_STANDARD 14)

# Add source files
file(GLOB_RECURSE SOURCES src/*)
add_executable(Textual_Game ${SOURCES})

if(WIN32 OR MSVC)
    # Download PDCurses
    include(FetchContent)
    FetchContent_Declare(
        PDCurses
        GIT_REPOSITORY https://github.com/wmcbrine/PDCurses.git
        GIT_TAG 3.9
    )

    FetchContent_GetProperties(PDCurses)
    if(NOT PDCurses_POPULATED)
        FetchContent_Populate(PDCurses)
        file(GLOB_RECURSE PDCurses_Source ${pdcurses_SOURCE_DIR}/pdcurses/*)
        file(GLOB_RECURSE PDCurses_Windows ${pdcurses_SOURCE_DIR}/wincon/*)
        file(GLOB PDCurses_Headers ${pdcurses_SOURCE_DIR}/*.h)
        add_library(PDCurses ${PDCurses_Source} ${PDCurses_Windows} ${PDCurses_Headers})
        target_include_directories(PDCurses PUBLIC ${pdcurses_SOURCE_DIR})
    endif()

    # Link libraries
    target_link_libraries(Textual_Game PRIVATE PDCurses)
else()
    # Link curses
    find_package(Curses REQUIRED)
    target_link_libraries(Textual_Game PRIVATE ${CURSES_LIBRARIES})
    target_include_directories(Textual_Game PRIVATE ${CURSES_INCLUDE_DIR})
endif()
