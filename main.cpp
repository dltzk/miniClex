#include "lexer.h"
#include "shuntingYard.h"
#include <fstream>
#include <stack>

using Lexem = std::pair<std::string, std::string>;
std::fstream streamline(R"(C:\Users\ivukhov\Source\Repos\miniClex\code.txt)");
Lexer lexer(streamline);

bool E() {
    if (!E7()) {
        return false;
    }
    return true;
}

bool E7() {
    if (!E6() && !E7_shtrih()) {
        return false;
    }
    return true;
}

bool E7_shtrih() {
    if (lexer.nextLexem().first == "opor"){
        if (!E6()) {
            return false;
        }
        if (!E7_shtrih()) {
            return false;
        }
        return true;
    }
    return true;
}

bool E6() {
    if (!E5()) {
        return false;
    }
    if (!E6_shtrih()) {
        return false;
    }
    return true;
}

bool E6_shtrih() {
    if (lexer.nextLexem().first == "opand") {
        if (!E5()) {
            return false;
        }
        if (!E6_shtrih()) {
            return false;
        }
        return true;
    }
    return true;
}

bool E5() {
    if (!E4()) {
        return false;
    }
    if (!E5_shtrih()) {
        return false;
    }
    return true;
}

bool E5_shtrih() {
    if (lexer.nextLexem().first == "opeq") {
        if (!E4()) {
            return false;
        }
        return true;
    }
    if (lexer.nextLexem().first == "opnot") {
        if (!E4()) {
            return false;
        }
        return true;
    }
    if (lexer.nextLexem().first == "oplt") {
        if (!E4()) {
            return false;
        }
        return true;
    }
    return true;
}

bool E4() {
    if (!E3()) {
        return false;
    }
    if (!E4_shtrih()) {
        return false;
    }
    return true;
}

bool E4_shtrih() {
    if (lexer.nextLexem().first == "opplus") {
        if (!E3()) {
            return false;
        }
        if (!E4_shtrih()) {
            return false;
        }
        return true;
    }
    if (lexer.nextLexem().first == "opminus") {
        if (!E3()) {
            return false;
        }
        if (!E4_shtrih()) {
            return false;
        }
        return true;
    }
    return true;
}

bool E3() {
    if (!E2()) {
        return false;
    }
    if (!E3_shtrih()) {
        return false;
    }
    return true;
}

bool E3_shtrih() {
    if (lexer.nextLexem().first == "opmul") {
        if (!E2()) {
            return false;
        }
        if (!E3_shtrih()) {
            return false;
        }
        return true;
    }
    return true;
}

bool E2() {
    if (lexer.nextLexem().first == "opnot") {
        if (!E2()) {
            return false;
        }
        return true;
    }
    if (!E1()) {
        return false;
    }
    return true;
}

bool E1() {
    if (lexer.nextLexem().first == "opinc") {
        if (lexer.nextLexem().first == "id") {
            return true;
        }
        return false;
    }
    if (lexer.nextLexem().first == "num") {
        return true;
    }
    if (lexer.nextLexem().first == "id") {
        if (!E1_shtrih()) {
            return false;
        }
        return true;
    }
    if (lexer.nextLexem().first == "lbrace") {
        if (!E1()) {
            return false;
        }
        if (lexer.nextLexem().first == "rbrace") {
            return true;
        }
    }
    return false;
}

bool E1_shtrih() {
    if (lexer.nextLexem().first == "opinc") {
        return true;
    }
    return true;
}

int main() {
    Lexem lexem;
    while (true) {
        lexem = lexer.nextLexem();
        std::cout << "{ \"" << lexem.first << "\", \"" << lexem.second << "\" }" << std::endl;
        if (lexem.first == "error" || lexem.first == "end") {
            break;
        }
    }
}
