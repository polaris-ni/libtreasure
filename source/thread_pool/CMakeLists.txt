project(tr_thread_pool C)

set(CMAKE_C_STANDARD 99)
add_definitions("-DTREASURE_LOG_MIN_LEVEL=0")
aux_source_directory(./ SRC_TR_THREAD_POOL)
add_library(tr_thread_pool SHARED ${SRC_TR_THREAD_POOL})
target_include_directories(tr_thread_pool PUBLIC ./)
target_link_libraries(tr_thread_pool PUBLIC treasure_common)
