cmake_minimum_required (VERSION 3.0)
set(PROJECTNAME Smol16)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
project(${PROJECTNAME})
include(FindPkgConfig)
include(ExternalProject)

# Libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDLMIXER_INCLUDE_DIR})

ExternalProject_Add(project_luajit
    URL http://luajit.org/download/LuaJIT-2.0.4.tar.gz
    CONFIGURE_COMMAND ""
    BUILD_COMMAND make -j4
    INSTALL_COMMAND ""
    PREFIX=${CMAKE_CURRENT_BINARY_DIR}/luajit-2.0.4
    BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR}/luajit/
    BUILD_IN_SOURCE 1
)
ExternalProject_Get_Property(project_luajit install_dir)
add_library(luajit STATIC IMPORTED)
set_property(TARGET luajit PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/project_luajit-prefix/src/project_luajit/src/libluajit.a)
add_dependencies(luajit project_luajit)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/project_luajit-prefix/src/project_luajit/src/)

# Includes
include_directories("${PROJECT_SOURCE_DIR}/lib/spdlog/include/")
include_directories("${PROJECT_SOURCE_DIR}/lib/cxxopts/include/")
include_directories("${PROJECT_SOURCE_DIR}/lib/luabridge/Source/LuaBridge/")
include_directories(src/includes)
include_directories("${PROJECT_BINARY_DIR}")
# Configuration files
configure_file (
    "${PROJECT_SOURCE_DIR}/src/includes/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)
# Data files
configure_file("${PROJECT_SOURCE_DIR}/res/font.png" "${PROJECT_BINARY_DIR}/data/font.png" COPYONLY)
add_custom_target(carts ALL
DEPENDS  ${CMAKE_CURRENT_BINARY_DIR}/carts_fake.h)
add_custom_target(std ALL
DEPENDS  ${CMAKE_CURRENT_BINARY_DIR}/std_fake.h)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/std_fake.h POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
               ${CMAKE_SOURCE_DIR}/src/std/ $<TARGET_FILE_DIR:${PROJECTNAME}>/data/std/)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/carts_fake.h POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
               ${CMAKE_SOURCE_DIR}/res/carts/ $<TARGET_FILE_DIR:${PROJECTNAME}>/carts/)

# Project
file(GLOB SOURCES "src/*.cxx")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++14 -g -pg -ggdb -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++14 -O3")

add_executable(${PROJECTNAME} ${SOURCES})
target_link_libraries(${PROJECTNAME} m dl luajit ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDLMIXER_LIBRARY})
