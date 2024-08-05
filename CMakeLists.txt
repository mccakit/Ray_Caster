cmake_minimum_required(VERSION 3.28)
project(Chapter_5)

set(CMAKE_CXX_STANDARD 23)

add_executable(Chapter_5 main.cpp
        c_with_classes.h
        vector_math.h
        matrix_transformations.h
        ppm.h
        intersections.h)
