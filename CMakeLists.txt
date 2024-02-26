cmake_minimum_required(VERSION 3.27)
project(miniClex)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES main.cpp)

add_executable(miniClex_run ${SOURCE_FILES})

include_directories(lexer_lib)
add_subdirectory(lexer_lib)

target_link_libraries(miniClex_run lexer_lib)

add_subdirectory(lexer_lib/google_tests)