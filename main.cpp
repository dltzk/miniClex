#include "lexer.h"
#include <fstream>
#include <iomanip>

using Lexem = std::pair<std::string, std::string>;


int main() {
    Lexem lexem;
    std::fstream streamline(R"(C:\Users\Juzo Suzuya\CLionProjects\miniClex\thirdtestfile.txt)");
    Lexer lexer(streamline);
//    std::cout << "{";
    while (true){
        lexem = lexer.nextLexem();
//        std::cout << "{\"" << lexem.first << "\", \"" << lexem.second << "\"},";

        std::cout << std::setw(16) << std::left << lexem.first << "\"" << lexem.second << "\"" << std::endl;
        if (lexem.first == "error" or lexem.first == "end") {
            break;
        }
    }
//    std::cout << "}";
}
