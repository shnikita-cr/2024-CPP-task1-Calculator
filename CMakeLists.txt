cmake_minimum_required(VERSION 3.25)
project(task1)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")

add_executable(task1 src/main.cpp
        src/Calculator/Calculator.h
        src/Operation/ArityOperation/UnaryOperation.h
        src/Operation/ArityOperation/BinaryOperation.h
        src/Tech/tech.cpp src/Parser/Parser.cpp
        src/Operation/OperationType/OperationType.h
        src/Calculator/Plugin.h
        src/Calculator/Calculator.cpp src/Calculator/Calculator.cpp)
