cmake_minimum_required(VERSION 3.20)
project(gamemenu)

set(VERSION_MAJOR 2)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

set(CMAKE_CXX_STANDARD 20)

if (NOT DEFINED LINK_TYPE)
    message("Library link type not specified, using default - STATIC")
    set(LINK_TYPE STATIC)
endif()

include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 11b73743c42cf7ecd7c596ba83fdbf1150ffa96c
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(SFML)


set(SOURCES 
    "public/game_menu/game_menu.h"
    "src/game_menu_impl.cpp"
)

add_library(gamemenu ${LINK_TYPE} ${SOURCES})
target_link_libraries(gamemenu PUBLIC sfml-graphics)
target_include_directories(
    gamemenu
    PUBLIC
    "public"
    "include"
)

set(GMENU_HEADERS
    "public/game_menu/game_menu.h"
)

set_target_properties(gamemenu PROPERTIES
    FRAMEWORK TRUE
    FRAMEWORK_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
    MACOSX_FRAMEWORK_IDENTIFIER in.sidhin.gamemenu
    MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
    MACOSX_FRAMEWORK_BUNDLE_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
    PUBLIC_HEADER "${GMENU_HEADERS}")

if(WIN32)
    add_custom_command(
        TARGET CMakeSFMLProject
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:CMakeSFMLProject>
        VERBATIM)
endif()

SET(BUILD_WITH_EXAMPLE OFF CACHE BOOL "Build attached example")

if(BUILD_WITH_EXAMPLE)
    add_executable(example 
        "examples/sample_menu.cpp"
    )
    target_link_libraries(example PRIVATE gamemenu)
    add_custom_target(copy_example_font
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/examples/sansation.ttf ${CMAKE_BINARY_DIR}
    )
    add_dependencies(example copy_example_font)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)