cmake_minimum_required (VERSION 3.0)
set(PROJECTNAME Smol16)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
project(${PROJECTNAME})
include(FindPkgConfig)
include(ExternalProject)

SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY
   ${PROJECT_BINARY_DIR}/./
   CACHE PATH
   "Single Directory for all Libraries"
   )

# --------- Setup the Executable output Directory -------------
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY
   ${PROJECT_BINARY_DIR}/./
   CACHE PATH
   "Single Directory for all Executables."
   )

# --------- Setup the Executable output Directory -------------
SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY
   ${PROJECT_BINARY_DIR}/./
   CACHE PATH
   "Single Directory for all static libraries."
   )


set (CXX_OPT_FLAGS "-s -fomit-frame-pointer -fno-stack-protector -fno-unroll-loops -ffast-math -flto")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -Wodr")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CMAKE_CXX_FLAGS} -g -Og ${CXX_OPT_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CMAKE_CXX_FLAGS} -Os ${CXX_OPT_FLAGS}")
# Libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDLMIXER_INCLUDE_DIR})

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
#add_executable(${PROJECTNAME} ${SOURCES})

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
