cmake_minimum_required(VERSION 3.5)
project(03_A_Fractal C)

set(CMAKE_C_STANDARD 11)

file(GLOB_RECURSE SOURCE_FILES src/*.c src/fractals/*.c)

add_executable(03_A_Fractal main.c ${SOURCE_FILES})
target_include_directories(03_A_Fractal PRIVATE include)