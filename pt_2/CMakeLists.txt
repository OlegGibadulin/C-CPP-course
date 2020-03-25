cmake_minimum_required(VERSION 3.0)

project(pt_2)
set(CMAKE_C_COMPILER g++)
set(CMAKE_C_FLAGS "-fprofile-arcs -ftest-coverage -fPIC -O0 -pthread -Wall -Werror -Wpedantic")

ADD_LIBRARY(linear_realization STATIC file_top.c trie.c)
ADD_LIBRARY(parallel_realization SHARED file_top.c trie.c)

add_executable(main_l.exe main.c input.c metrics.c)
add_executable(main_p.exe main.c input.c metrics.c)

TARGET_LINK_LIBRARIES(main_l.exe linear_realization)
TARGET_LINK_LIBRARIES(main_p.exe parallel_realization)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_l.exe test.c)
add_executable(test_p.exe test.c)

target_link_libraries(test_l.exe ${GTEST_LIBRARIES} pthread linear_realization)
target_link_libraries(test_p.exe ${GTEST_LIBRARIES} pthread parallel_realization)
