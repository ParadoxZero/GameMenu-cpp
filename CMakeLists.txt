cmake_minimum_required(VERSION 3.20)
project(gamemenu)

set(MAJOR_VERSION 2)
set(MINOR_VERSION 0)
set(PATCH_VERSION 0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_OSX_ARCHITECTURES "arm64")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wno-error=unused-command-line-argument")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wno-error=unused-command-line-argument")

if (NOT DEFINED LINK_TYPE)
    message("Library link type not specified, using default - STATIC")
    set(LINK_TYPE STATIC)
endif()

# set(SFML_STATIC_LIBRARIES TRUE)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 11b73743c42cf7ecd7c596ba83fdbf1150ffa96c
    GIT_SHALLOW TRUE
    # SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/sfml
)

FetchContent_MakeAvailable(SFML)


set(SOURCES 
    "include/GameMenu/GameMenu.h"
    "src/GameMenu/GameMenu.cpp"
)

add_library(gamemenu ${LINK_TYPE} ${SOURCES})
target_link_libraries(gamemenu PUBLIC sfml-graphics)
target_include_directories(
    gamemenu
    PUBLIC
    "public"
    "include"
)

if(WIN32)
    add_custom_command(
        TARGET CMakeSFMLProject
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:CMakeSFMLProject>
        VERBATIM)
endif()



add_executable(example 
"examples/sample_menu.cpp"
"include/GameMenu/GameMenu.h"
)
target_link_libraries(example PRIVATE gamemenu)
target_include_directories(
    example
    PRIVATE
    "public"
    "include"
)

add_custom_target(copy_example_font
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Examples/sansation.ttf ${CMAKE_BINARY_DIR}
)

add_dependencies(example copy_example_font)