cmake_minimum_required(VERSION 3.26)
project(PROJETO_AED)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(PROJETO_AED
        Code/Data.h
        Code/Functions.cpp
        Code/Functions.h
        Code/ReadData.h
        Code/tests.cpp
        Code/ReadData.cpp
        Code/ReadData.cpp
)
