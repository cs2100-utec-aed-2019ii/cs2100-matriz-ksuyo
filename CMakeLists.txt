cmake_minimum_required(VERSION 3.15)
project(cs2100_matriz_ksuyo)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(cs2100_matriz_ksuyo
        Macros.h
        main.cpp
        README.md
        SparseMatrix.h Nodes.h Pixel.h)
