//
// Created by Juzo Suzuya on 05.03.2024.
//

#ifndef LEX_TESTS_SHUNTINGYARD_H
#define LEX_TESTS_SHUNTINGYARD_H

#include "lexer.h"
#include <iostream>
#include <string>
#include <vector>
#include <stack>

class ShuntingYard {
public:
    ShuntingYard(std::istream&);
    virtual ~ShuntingYard();
    Lexem getNextLexem();
protected:
private:
    Lexer lexer;
    bool unclosed = false;
    void findLexem(const Lexem& lexem);
    std::vector<Lexem> output;
    std::stack<std::string> stack;
};

#endif // LEX_TESTS_SHUNTINGYARD_H