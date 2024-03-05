project(lexer_lib)
# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'test1.cpp test2.cpp' are source files with tests
add_executable(LexerTesting minictester.cpp)

target_link_libraries(LexerTesting lexer_lib)
target_link_libraries(LexerTesting gtest gtest_main)