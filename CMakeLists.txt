cmake_minimum_required(VERSION 3.26)
project(PROJETO_AED)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(PROJETO_AED
        Code/Data.h
        Code/Data.cpp
        Code/Functions.cpp
        Code/Functions.h
        Code/ReadData.h
        Code/tests.cpp
        Code/ReadData.cpp

        Code2/Data.h
        Code2/Data.cpp
        Code2/ReadData.h
        Code2/tests.cpp
        Code2/ReadData.cpp

)
