#include "lexer.h"
#include <fstream>
#include <iomanip>
#include <stack>

using Lexem = std::pair<std::string, std::string>;


int main() {
    Lexem lexem;
    std::fstream streamline(R"(C:\Users\Juzo Suzuya\CLionProjects\miniClex\code.txt)");
    Lexer lexer(streamline);
//    std::cout << "{";
    std::stack<std::string> stack;
    std::vector<std::pair<std::string, std::string>> output;
    while (true){
        lexem = lexer.nextLexem();
//        std::cout << "{\"" << lexem.first << "\", \"" << lexem.second << "\"},";

//        std::cout << std::setw(16) << std::left << lexem.first << "\"" << lexem.second << "\"" << std::endl;
        if (lexem.first == "error" or lexem.first == "end") {
            break;
        }

        if (lexem.first == "num"){
            output.push_back({lexem.second, lexem.first});
        }
        else if (lexem.first == "opmul"){
            if (stack.empty()){
                stack.push(lexem.first);
            }
            else if (stack.top() == "opmul"){
                std::string a = stack.top();
                output.push_back({" ", a});
                stack.pop();
                stack.push(lexem.first);
            }
            else if (stack.top() == "opplus"){
                stack.push(lexem.first);
            }
        }
        else if (lexem.first == "opplus"){
            if (stack.empty()){
                stack.push(lexem.first);
            }
            else if (stack.top() == "opplus"){
                std::string a = stack.top();
                output.push_back({" ", a});
                stack.pop();
                stack.push(lexem.first);
            }
            else if(stack.top() == "opmul"){
                while (stack.top() == "opmul") {
                    std::string a = stack.top();
                    output.push_back({" ", a});
                    stack.pop();
                    if (stack.empty()){
                        stack.push(lexem.first);
                        break;
                    }
                    else if (stack.top() == "opplus") {
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
    if (!stack.empty()){
        for (int i = 0; i <= stack.size(); i++){
            std::string a = stack.top();
            output.push_back({" ", a});
            stack.pop();
        }
    }
    for (int i = 0; i < output.size(); i++){
        std::cout << "\"" << output[i].first << "\"" << " " << output[i].second << std::endl;
    }
//    std::cout << "}";
}
