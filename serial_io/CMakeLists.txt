cmake_minimum_required(VERSION 3.8)

project(serial_io)

add_library(logger STATIC src/logger.c)
target_include_directories(logger PUBLIC include)

add_executable(serial_io main.c)

target_link_libraries(serial_io PUBLIC logger)