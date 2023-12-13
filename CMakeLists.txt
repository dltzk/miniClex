cmake_minimum_required(VERSION 3.27)
project(miniClex)

set(CMAKE_CXX_STANDARD 20)

add_executable(miniClex main.cpp
        source/lexer.cpp
        headers/lexer.h
        source/lexicalGraph.cpp
        headers/lexicalGraph.h)
