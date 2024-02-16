project(treasure_common C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSIMPLE_FILENAME='\"$(subst  ${CMAKE_SOURCE_DIR}/,,$(abspath $<))\"'")

aux_source_directory(./ SRC_COMMON)
add_library(treasure_common STATIC ${SRC_COMMON})
target_include_directories(treasure_common PUBLIC ./)
