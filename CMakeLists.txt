cmake_minimum_required(VERSION 3.26)
project(libtreasure C)

set(CMAKE_C_STANDARD 11)

set(TREASURE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(source)
add_subdirectory(test)
