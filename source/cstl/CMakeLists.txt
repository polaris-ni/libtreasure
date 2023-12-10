project(cstl C)

set(CMAKE_C_STANDARD 99)

aux_source_directory(./ SRC_CSTL)
add_library(cstl SHARED ${SRC_CSTL})
target_include_directories(cstl PUBLIC ./)
