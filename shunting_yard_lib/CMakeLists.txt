project(shunting_yard_Lib)
cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_library(shunting_yard_lib src/shuntingYard.cpp)
target_include_directories(shunting_yard_lib PUBLIC include)


