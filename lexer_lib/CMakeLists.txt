project(lexer_lib)


set(SOURCE_FILES lexer.cpp lexicalGraph.cpp)
set(HEADER_FILES lexer.h lexicalGraph.h)

add_library(lexer_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
