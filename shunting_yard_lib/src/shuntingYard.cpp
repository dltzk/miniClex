#include "shuntingYard.h"
#include <iostream>

ShuntingYard::ShuntingYard(std::istream &streamline) : lexer { streamline } {}

ShuntingYard::~ShuntingYard() = default;

void ShuntingYard::findLexem(const Lexem& lexem) {
    if (lexem.first == "num" or lexem.first == "id") {
        output.push_back({lexem.first, lexem.second});
    } else if (lexem.first == "lpar"){
        stack.push(lexem.first);
        unclosed = true;
    } else if (lexem.first == "rpar"){
        while (!stack.empty()) {
            if (stack.top() == "lpar") {
                stack.pop();
                unclosed = false;
                break;
            }
            output.push_back({stack.top(), ""});
            stack.pop();

            if (stack.empty()) {
                output.push_back({"error", ""});
            }
        }
    } else if (lexem.first == "opmul") {
        if (stack.empty() or stack.top() == "opplus" or stack.top() == "opminus" or stack.top() == "lpar") {
            stack.push(lexem.first);
        } else if (stack.top() == "opmul" or stack.top() == "lpar") {
            output.push_back({stack.top(), ""});
            stack.pop();
            stack.push(lexem.first);
        }
    } else if (lexem.first == "opplus" or lexem.first == "opminus") {
        if (stack.empty() or stack.top() == "lpar") {
            stack.push(lexem.first);
        } else if (stack.top() == "opplus" or stack.top() == "opminus") {
            output.push_back({stack.top(), ""});
            stack.pop();
            stack.push(lexem.first);
        } else if (stack.top() == "opmul") {
            while (!stack.empty()) {
                output.push_back({stack.top(), ""});
                stack.pop();
                if (stack.empty()) {
                    break;
                } else if (stack.top() == "opplus" or stack.top() == "opminus") {
                    output.push_back({stack.top(), ""});
                    stack.pop();
                    break;
                } else if (stack.top() == "lpar"){
                    break;
                }
            }
            stack.push(lexem.first);
        }
    }
    else if (lexem.first == "end"){
        if (!stack.empty()) {
            for (int i = 0; i <= stack.size(); i++) {
                if (stack.top() == "lpar" and unclosed){
                    output.push_back({"error", ""});
                    break;
                }
                output.push_back({stack.top(), ""});
                stack.pop();
            }
            output.push_back({"end", ""});
        }
    }
}

Lexem ShuntingYard::getNextLexem() {
    Lexem a;
    while (output.empty()) {
        findLexem(lexer.nextLexem());
    }
    if (output.front().first == "end"){
        return output.front();
    }

    a = output.front();
    output.erase(output.begin());
    return a;
}