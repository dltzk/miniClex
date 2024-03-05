project(lexer_lib)
cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_library(lexer_lib src/lexer.cpp src/lexicalGraph.cpp)
target_include_directories(lexer_lib PUBLIC include)

#set(SOURCE_FILES lexer.cpp lexicalGraph.cpp)
#set(HEADER_FILES lexer.h lexicalGraph.h)
#
#add_library(lexer_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
