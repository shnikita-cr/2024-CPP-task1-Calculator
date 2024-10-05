cmake_minimum_required(VERSION 3.25)
project(task1)

set(CMAKE_CXX_STANDARD 17)

add_executable(task1 src/main.cpp src/Calculator/Calculator.h src/Operations/Operation/Operation.h src/Token.h src/Parser/Parser.cpp src/Parser/Parser.h src/tech.h src/tech.cpp)
