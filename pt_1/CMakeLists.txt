cmake_minimum_required(VERSION 3.0)

project(pt_1)
set(CMAKE_C_COMPILER g++)
set(CMAKE_C_FLAGS "-fprofile-arcs -ftest-coverage -fPIC -O0")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test.exe test.c ticket.c)
target_link_libraries(test.exe ${GTEST_LIBRARIES} pthread)

add_executable(main.exe main.c input.c ticket.c)