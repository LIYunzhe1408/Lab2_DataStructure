cmake_minimum_required(VERSION 3.19)
project(test)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c*)

add_executable(test ${SRC})