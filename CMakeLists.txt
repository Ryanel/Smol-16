cmake_minimum_required (VERSION 3.0)

set(PROJECTNAME Smol16)

project(${PROJECTNAME})

INCLUDE(FindPkgConfig)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
#set(LUA_LIBRARY "/usr/lib/liblua.so;dl")
find_package(SDL2 REQUIRED)
find_package(Lua REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${LUA_INCLUDE_DIR})

# Manually included libs
include_directories("${PROJECT_SOURCE_DIR}/lib/Selene/include/")
include_directories("${PROJECT_SOURCE_DIR}/lib/cxxopts/include/")
include_directories("${PROJECT_SOURCE_DIR}/lib/spdlog/include/")
configure_file (
    "${PROJECT_SOURCE_DIR}/src/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)

include_directories(src/includes)
include_directories("${PROJECT_BINARY_DIR}")
file(GLOB SOURCES "src/*.cxx" "src/smol16/*.cxx")
configure_file("${PROJECT_SOURCE_DIR}/src/std/std.lua" "${PROJECT_BINARY_DIR}/data/std.lua" COPYONLY)
configure_file("${PROJECT_SOURCE_DIR}/res/font.png" "${PROJECT_BINARY_DIR}/data/font.png" COPYONLY)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g -O2")

add_executable(${PROJECTNAME} ${SOURCES})
target_link_libraries(${PROJECTNAME} ${LUA_LIBRARIES} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})

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
