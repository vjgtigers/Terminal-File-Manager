cmake_minimum_required(VERSION 3.28)
project(TFV)

set(CMAKE_CXX_STANDARD 26)

add_executable(TFV main.cpp
        keyTracker.cpp
        keyTracker.h
        terminalCommands.cpp
        terminalCommands.h
        miscFunctions.cpp
        miscFunctions.h
        drawLayout.cpp
        drawLayout.h)

set(GCC_COVERAGE_COMPILE_FLAGS "-static")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )