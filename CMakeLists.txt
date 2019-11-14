cmake_minimum_required(VERSION 3.15)
project(cs2100_matriz_ksuyo)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(cs2100_matriz_ksuyo
        Macros.h
        main.cpp
        SparseMatrix.h Nodes.h Pixel.h)


find_package(OpenCV REQUIRED)
set(SOURCE_FILES main.cpp Macros.h SparseMatrix.h Nodes.h Pixel.h)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )