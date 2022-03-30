cmake_minimum_required(VERSION 3.19)
project(test)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(AdjMatrixUndirGraph.h
        Assistance.h
        TestAdjMatrixUndirGraph.cpp)