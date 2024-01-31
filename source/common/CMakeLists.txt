project(treasure_common C)

set(CMAKE_C_STANDARD 11)

aux_source_directory(./ SRC_COMMON)
add_library(treasure_common SHARED ${SRC_COMMON})
target_include_directories(treasure_common PUBLIC ./)
