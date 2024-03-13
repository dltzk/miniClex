cmake_minimum_required(VERSION 3.14)
project(lex-lib)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(shunting_yard_lib src/shuntingYard.cpp)
target_link_libraries(shunting_yard_lib lexer_lib)
target_include_directories(shunting_yard_lib PUBLIC include)