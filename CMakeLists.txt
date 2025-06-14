cmake_minimum_required(VERSION 3.18)

project(simpledb)

set(CMAKE_C_STANDARD 11)

add_library(simpledb_core STATIC
    block_id.c
    page.c)

target_include_directories(simpledb_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(simpledb simpledb.c)
target_link_libraries(simpledb PRIVATE simpledb_core)

enable_testing()
add_subdirectory(unity)

add_executable(test_page page_test.c)
target_link_libraries(test_page PRIVATE simpledb_core unity)
target_include_directories(test_page PRIVATE unity/src)
add_test(NAME test_page COMMAND test_page)
