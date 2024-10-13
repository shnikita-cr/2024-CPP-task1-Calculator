cmake_minimum_required(VERSION 3.25)
project(Factorial)

set(CMAKE_CXX_STANDARD 17)

include_directories(../task1/src/Operation)
add_library(Factorial SHARED library.cpp)
