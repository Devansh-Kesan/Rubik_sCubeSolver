cmake_minimum_required(VERSION 3.31)
project(Rubik_sCubeSolver)

set(CMAKE_CXX_STANDARD 20)

add_executable(Rubik_sCubeSolver main.cpp
        Model/RubiksCube.cpp
        Model/RubiksCube.h
        Model/RubiksCube3dArray.cpp)
