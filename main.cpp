#include "lexer.h"
#include "shuntingYard.h"
#include <fstream>
#include <stack>

using Lexem = std::pair<std::string, std::string>;


int main() {
    Lexem lexem;
    std::fstream streamline(R"(C:\Users\Juzo Suzuya\CLionProjects\miniClex\code.txt)");
    ShuntingYard SYM(streamline);
    while (true) {
        lexem = SYM.getNextLexem();
        std::cout << "{ \"" << lexem.first << "\", \"" << lexem.second << "\" }" << std::endl;
        if (lexem.first == "error" or lexem.first == "end") {
            break;
        }
    }
}
