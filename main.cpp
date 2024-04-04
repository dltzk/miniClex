#include "lexer.h"
#include <fstream>
#include <stack>
#include <vector>

using Lexem = std::pair<std::string, std::string>;
std::fstream streamline(R"(C:\Users\Juzo Suzuya\CLionProjects\miniClex\code.txt)");
Lexer lexer(streamline);
std::vector<std::string> temp = {};
int pointer = 0;
bool E();
bool E1();
bool E2();
bool E3();
bool E4();
bool E5();
bool E6();
bool E7();
bool E7_shtrih();
bool E6_shtrih();
bool E5_shtrih();
bool E4_shtrih();
bool E3_shtrih();
bool E1_shtrih();

bool E1_shtrih() {
    if (temp[pointer] == "opinc"){
        pointer += 1;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
    }
    return true;
}

bool E1() {
    if (temp[pointer] == "end"){
        return false;
    }
    if (temp[pointer] == "opinc") {
        pointer += 1;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (temp[pointer] == "id") {
            pointer += 1;
            std::string a = lexer.nextLexem().first;
            temp.push_back(a);
            return true;
        }
        return false;
    }
    else if (temp[pointer] == "num") {
        pointer += 1;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        return true;
    }
    else if (temp[pointer] == "id") {
        pointer += 1;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (!E1_shtrih()){
            return false;
        }
        return true;
    }
    else if (temp[pointer] == "lpar") {
        pointer += 1;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (!E()) {
            return false;
        }
        if (temp[pointer] == "rpar") {
            pointer += 1;
            std::string a = lexer.nextLexem().first;
            temp.push_back(a);
            return true;
        }
    }
    return false;
}

bool E2() {
    if (temp[pointer] == "opnot") {
        pointer += 1;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
    }
    if (!E1()) {
        return false;
    }
    return true;
}

bool E3_shtrih() {
    if (temp[pointer] == "end"){
        return true;
    }
    if (temp[pointer] == "opmul") {
        pointer += 1;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (!E2()) {
            return false;
        }
        if (!E3_shtrih()) {
            return false;
        }
    }
    return true;
}

bool E3() {
    if (!E2()) {
        return false;
    }
    if (!E3_shtrih()){
        return false;
    }
    return true;
}

bool E4_shtrih() {
    if (temp[pointer] == "end"){
        return true;
    }
    if (temp[pointer] == "opplus") {
        pointer += 1;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (!E3()) {
            return false;
        }
        if (!E4_shtrih()) {
            return false;
        }
    }
    if (temp[pointer] == "opminus") {
        pointer += 1;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (!E3()) {
            return false;
        }
        if (!E4_shtrih()) {
            return false;
        }
    }
    return true;
}

bool E4() {
    if (!E3()) {
        return false;
    }
    if (!E4_shtrih()){
        return false;
    }
    return true;
}

bool E5_shtrih() {
    if (temp[pointer] == "end"){
        return true;
    }
    if (temp[pointer] == "opeq") {
        pointer += 1;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (!E4()) {
            return false;
        }
    }
    else if (temp[pointer] == "opnot") {
        pointer += 1;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (!E4()) {
            return false;
        }
    }
    else if (temp[pointer] == "oplt") {
        pointer += 1;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (!E4()) {
            return false;
        }
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


bool E6_shtrih() {
    if (temp[pointer] == "end"){
        return true;
    }
    if (temp[pointer] == "opand") {
        pointer += 1;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (!E5()) {
            return false;
        }
        if (!E6_shtrih()) {
            return false;
        }
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

bool E7_shtrih() {
    if (temp[pointer] == "end"){
        return true;
    }
    if (temp[pointer] == "opor") {
        pointer += 1;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (!E6()) {
            return false;
        }
        if (!E7_shtrih()) {
            return false;
        }
    }
    return true;
}

bool E7() {
    if (!E6()){
        return false;
    }
    if (!E7_shtrih()) {
        return false;
    }
    return true;
}

bool E() {
    if (!E7()) {
        return false;
    }
    return true;
}

int main() {
    Lexem lexem;
    std::string a = lexer.nextLexem().first;
    temp.push_back(a);
    bool A = E();
    if (A and temp[pointer] == "end"){
        std::cout << "Correct expression";
    } else {
        std::cout << "Incorrect expression";
    }

}