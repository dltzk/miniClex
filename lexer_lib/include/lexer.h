#ifndef MINICLEX_LEXER_H
#define MINICLEX_LEXER_H
#include "lexicalGraph.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using Lexem = std::pair<std::string, std::string>;

class Lexer {
private:
    std::istream &streamline;
    char cache;
    int state = 0;
    std::string buffer;
    void findLexem(std::vector<Container> graph, Lexem &lexem);

public:
    Lexer(std::istream& streamline);
    Lexem nextLexem();
};

#endif //MINICLEX_LEXER_H
