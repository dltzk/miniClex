//
// Created by Juzo Suzuya on 05.03.2024.
//
#include <iostream>

class ShuntingYard {
private:
    std::istream &streamline;
    char cache;
    void findLexem(std::vector<Container> graph, Lexem &lexem);

public:
    ShuntingYard(std::istream& streamline);
    ShuntingYard nextLexem();
};