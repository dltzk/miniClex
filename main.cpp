#include "lexer.h"
#include <fstream>
#include <stack>

using Lexem = std::pair<std::string, std::string>;
std::fstream streamline(R"(C:\Users\TEMP.EDU\Source\Repos\miniClex\code.txt)");
Lexer lexer(streamline);

bool E1_shtrih(std::string temp = "") {
    if (temp == "opinc") {
        return true;
    }
    return true;
}

bool E1(std::string temp = "") {
    if (temp == "opinc") {
        std::string temp1 = lexer.nextLexem().first;
        if (temp1 == "id") {
            return true;
        }
        return false;
    }
    if (temp == "num") {
        return true;
    }
    if (temp == "id") {
        std::string temp1 = lexer.nextLexem().first;
        if (!E1_shtrih(temp1)) {
            return false;
        }
        return true;
    }
    //if (temp == "lbrace") {
    //    std::string temp1 = lexer.nextLexem().first;
    //    if (!E(temp1)) {
    //        return false;
    //    }
    //    if (temp1 == "rbrace") {
    //        return true;
    //    }
    //}
    return false;
}

bool E2(std::string temp = "") {
    if (temp == "opnot") {
        if (!E2(temp)) {
            return false;
        }
        return true;
    }
    if (!E1(temp)) {
        return false;
    }
    return true;
}

bool E3_shtrih(std::string temp = "") {
    if (temp == "opmul") {
        if (!E2(temp)) {
            return false;
        }
        if (!E3_shtrih(temp)) {
            return false;
        }
        return true;
    }
    return true;
}

bool E3(std::string temp = "") {
    if (!E2(temp)) {
        return false;
    }
    if (!E3_shtrih(temp)) {
        return false;
    }
    return true;
}

bool E4_shtrih(std::string temp = "") {
    if (temp == "opplus") {
        std::string temp1 = lexer.nextLexem().first;
        if (!E3(temp1)) {
            return false;
        }
        if (!E4_shtrih(temp1)) {
            return false;
        }
        return true;
    }
    if (temp == "opminus") {
        std::string temp1 = lexer.nextLexem().first;
        if (!E3(temp1)) {
            return false;
        }
        if (!E4_shtrih(temp1)) {
            return false;
        }
        return true;
    }
    return true;
}

bool E4(std::string temp = "") {
    if (!E3(temp)) {
        return false;
    }
    if (!E4_shtrih(temp)) {
        return false;
    }
    return true;
}

bool E5_shtrih(std::string temp = "") {
    if (temp == "opeq") {
        std::string temp1 = lexer.nextLexem().first;
        if (!E4(temp1)) {
            return false;
        }
        return true;
    }
    if (temp == "opnot") {
        std::string temp1 = lexer.nextLexem().first;
        if (!E4(temp1)) {
            return false;
        }
        return true;
    }
    if (temp == "oplt") {
        std::string temp1 = lexer.nextLexem().first;
        if (!E4(temp1)) {
            return false;
        }
        return true;
    }
    return true;
}

bool E5(std::string temp = "") {
    if (!E4(temp)) {
        return false;
    }
    if (!E5_shtrih(temp)) {
        return false;
    }
    return true;
}


bool E6_shtrih(std::string temp = "") {
    if (temp == "opand") {
        std::string temp1 = lexer.nextLexem().first;
        if (!E5(temp1)) {
            return false;
        }
        if (!E6_shtrih(temp1)) {
            return false;
        }
        return true;
    }
    return true;
}

bool E6(std::string temp = "") {
    if (!E5(temp)) {
        return false;
    }
    if (!E6_shtrih(temp)) {
        return false;
    }
    return true;
}

bool E7_shtrih(std::string temp = "") {
    if (temp == "opor") {
        std::string temp1 = lexer.nextLexem().first;
        if (!E6(temp1)) {
            return false;
        }
        if (!E7_shtrih(temp1)) {
            return false;
        }
        return true;
    }
    return true;
}

bool E7(std::string temp = "") {
    if (!E6(temp) || !E7_shtrih(temp)) {
        return false;
    }
    return true;
}

bool E(std::string temp = "") {
    if (!E7(temp)) {
        return false;
    }
    return true;
}


int main() {
    Lexem lexem;
    std::string zxc = lexer.nextLexem().first;
    bool A = E(zxc);
    std::cout << A;
}
