project(cstl C)

set(CMAKE_C_STANDARD 11)
add_definitions("-DTREASURE_LOG_MIN_LEVEL=0")
aux_source_directory(./ SRC_CSTL)
add_library(cstl SHARED ${SRC_CSTL})
target_include_directories(cstl PUBLIC ./)
target_link_libraries(cstl PUBLIC treasure_common)
