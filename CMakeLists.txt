cmake_minimum_required(VERSION 3.8)
project(ComputerSystemLab)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES expr4.c expr4.h)
add_executable(ComputerSystemLab ${SOURCE_FILES})