#include "..lexer_lib/lexer.h"
#include <fstream>
#include <stack>

using Lexem = std::pair<std::string, std::string>;


int main() {
    if (lexem.first == "error" or lexem.first == "end") {
        break;
    }

    if (lexem.first == "num") {
        output.push_back({lexem.second, lexem.first});
    } else if (lexem.first == "opmul") {
        if (stack.empty()) {
            stack.push(lexem.first);
        } else if (stack.top() == "opmul") {
            std::string a = stack.top();
            output.push_back({" ", a});
            stack.pop();
            stack.push(lexem.first);
        } else if (stack.top() == "opplus") {
            stack.push(lexem.first);
        }
    } else if (lexem.first == "opplus") {
        if (stack.empty()) {
            stack.push(lexem.first);
        } else if (stack.top() == "opplus") {
            std::string a = stack.top();
            output.push_back({" ", a});
            stack.pop();
            stack.push(lexem.first);
        } else if (stack.top() == "opmul") {
            while (stack.top() == "opmul") {
                std::string a = stack.top();
                output.push_back({" ", a});
                stack.pop();
                if (stack.empty()) {
                    stack.push(lexem.first);
                    break;
                } else if (stack.top() == "opplus") {
                    std::string a = stack.top();
                    output.push_back({" ", a});
                    stack.pop();
                    stack.push(lexem.first);
                    break;
                }
            }
        }
    }
};