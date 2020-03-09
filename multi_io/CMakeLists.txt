cmake_minimum_required(VERSION 3.8)

project(multi_io C CXX)

add_library(logger STATIC src/logger.c)
target_include_directories(logger PUBLIC include)

add_executable(multi_io main.c)

target_link_libraries(multi_io PUBLIC logger)