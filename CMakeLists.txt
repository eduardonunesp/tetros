cmake_minimum_required(VERSION 3.10)

project(Tetros VERSION 1.0)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")
add_executable(Tetros ${SOURCES})
target_compile_definitions(Tetros PRIVATE _DEBUG=1)
target_link_libraries(Tetros ${SDL2_LIBRARIES})
