cmake_minimum_required(VERSION 3.26)
project(T3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(T3
        commands.cpp
        commands.h
        dictionary.cpp
        dictionary.h
        helpFunctions.cpp
        helpFunctions.h
        main.cpp
        polygon.cpp
        polygon.h)
