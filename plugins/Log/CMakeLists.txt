cmake_minimum_required(VERSION 3.25)
project(Log10)

set(CMAKE_CXX_STANDARD 17)

include_directories(../task1/src/Operation)
add_library(Log10 SHARED library.h library.cpp)
