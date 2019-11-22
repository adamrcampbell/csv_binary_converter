cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_C_FLAGS "-Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "-g -O0")
set(CMAKE_C_FLAGS_RELEASE "-O3")

project(converter)
add_executable(converter main.c converter.c)
target_link_libraries(converter)
