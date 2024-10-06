cmake_minimum_required(VERSION 3.25)
project(task1)

set(CMAKE_CXX_STANDARD 17)

add_executable(task1 src/main.cpp
        src/Calculator/Calculator.h
        src/Operation/ArityOperation/UnaryOperation.h
        src/Operation/ArityOperation/BinaryOperation.h
        src/Tech/tech.cpp src/Parser/Parser.cpp
        src/Operation/OperationType/OperaitionType.h
        src/Operation/testOp.h src/Calculator/Plugin.h)
