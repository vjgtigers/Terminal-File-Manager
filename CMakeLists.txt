cmake_minimum_required(VERSION 3.28)
project(TFV)

set(CMAKE_CXX_STANDARD 26)

add_executable(TFV ./src/main.cpp
        ./src/keyTracker.cpp
        ./src/keyTracker.h
        ./src/terminalCommands.cpp
        ./src/terminalCommands.h
        ./src/miscFunctions.cpp
        ./src/miscFunctions.h
        ./src/drawLayout.cpp
        ./src/drawLayout.h
        ./src/commandLine.cpp
        ./src/commandLine.h
        ./src/commandLine.h
        ./src/commands.cpp
        ./src/commands.h
        ./src/commands.h
        ./src/configInfo.cpp
        ./src/configInfo.h
        ./src/liveSearch.cpp
        ./src/liveSearch.h)

set(GCC_COVERAGE_COMPILE_FLAGS "-static")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )