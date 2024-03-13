#cmake_minimum_required(VERSION 3.27)
#project(miniClex)
#
#set(CMAKE_CXX_STANDARD 20)
#
#set(SOURCE_FILES main.cpp)
#add_executable(miniClex_run ${SOURCE_FILES})
#
#add_subdirectory(lexer_lib)
#add_subdirectory(shunting_yard_lib)
#
#target_link_libraries(miniClex_run lexer_lib)
#target_link_libraries(miniClex_run shunting_yard_lib)

cmake_minimum_required(VERSION 3.14)
project(miniClex)

set(SOURCE_FILES main.cpp)
add_executable(miniClex_run ${SOURCE_FILES})
target_link_libraries(miniClex_run lexer_lib)
target_link_libraries(miniClex_run shunting_yard_lib)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lexer_lib)
add_subdirectory(shunting_yard_lib)
add_subdirectory(tests)