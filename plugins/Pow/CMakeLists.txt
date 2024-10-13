cmake_minimum_required(VERSION 3.25)
project(Pow)

set(CMAKE_CXX_STANDARD 17)

include_directories(../task1/src/Operation)
add_library(Pow SHARED library.cpp)
