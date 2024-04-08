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
bool StmtList();
bool Stmt();
bool DeclareStmt();
bool DeclareStmtList();
bool AssignOrCallOp();
bool WhileOp();
bool ForOp();
bool IfOp();
bool SwitchOp();
bool IOp();
bool OOp();
bool Type();
bool ParamList();
bool DeclVarList();
bool InitVar();
bool ParamList();
bool ParamListList();
bool AssignOrCall();
bool AssignOrCallOp();
bool AssignOrCallList();
bool ForInit();
bool ForExp();
bool ForLoop();
bool ArgList();


bool ForLoop(){
    if (temp[pointer] == "opinc"){
        pointer++;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (temp[pointer] == "id"){
            pointer++;
            std::string a = lexer.nextLexem().first;
            temp.push_back(a);
            return true;
        }
        return false;
    }

    int temp_point = pointer;
    if (AssignOrCall()){
        return true;
    }
    else {
        pointer = temp_point;
        return true;
    }
}

bool ForExp(){
    int temp_point = pointer;
    if (E()){
        return true;
    } else {
        pointer = temp_point;
        return true;
    }
}

bool ForInit(){
    int temp_point = pointer;
    if (AssignOrCall()){
        return true;
    } else {
        pointer = temp_point;
        return true;
    }
}

bool ForOp(){
    if (temp[pointer] == "kwfor"){
        pointer++;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (temp[pointer] == "lpar"){
            pointer++;
            std::string a = lexer.nextLexem().first;
            temp.push_back(a);
            if (!ForInit()){
                return false;
            }
            if (temp[pointer] == "semicolon"){
                pointer++;
                std::string a = lexer.nextLexem().first;
                temp.push_back(a);
                if (!ForExp()){
                    return false;
                }
                if (temp[pointer] == "semicolon"){
                    pointer++;
                    std::string a = lexer.nextLexem().first;
                    temp.push_back(a);
                    if (!ForLoop()){
                        return false;
                    }
                    if (temp[pointer] == "rpar"){
                        pointer++;
                        std::string a = lexer.nextLexem().first;
                        temp.push_back(a);
                        if (!Stmt()){
                            return false;
                        }
                        return true;
                    }

                }
            }
        }
    }
    return false;
}

bool WhileOp(){
    if (temp[pointer] == "kwwhile"){
        pointer++;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (temp[pointer] == "lpar"){
            pointer++;
            std::string a = lexer.nextLexem().first;
            temp.push_back(a);
            if (!E()){
                return false;
            }
            if (temp[pointer] == "rpar"){
                pointer++;
                std::string a = lexer.nextLexem().first;
                temp.push_back(a);
                return true;
            }
        }
    }
    return false;
}

bool AssignOrCallList(){
    if (temp[pointer] == "opassign"){
        pointer++;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (!E()){
            return false;
        }
        return true;
    }
    else if (temp[pointer] == "lpar"){
        pointer++;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (!ParamList()){
            return false;
        }
        return true;
    }
    else{
        return false;
    }
}

bool AssignOrCall(){
    if (temp[pointer] == "id"){
        pointer++;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (!AssignOrCallList()){
            return false;
        }
        return true;
    }
    return false;
}

bool AssignOrCallOp(){
    if (!AssignOrCall()){
        return false;
    }
    if (temp[pointer] != "semicolon"){
        return false;
    }
    pointer++;
    std::string a = lexer.nextLexem().first;
    temp.push_back(a);
    return true;
}

bool ParamListList(){
    if (temp[pointer] == "end"){
        return false;
    }

    if (temp[pointer] == "comma"){
        pointer++;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (!Type()){
            return false;
        }
        if (temp[pointer] == "id"){
            pointer++;
            std::string a = lexer.nextLexem().first;
            temp.push_back(a);
            if (!ParamList()){
                return false;
            }
        }
    }
    return true;
}

bool ParamList() {
    if (temp[pointer] == "end") {
        return false;
    }

    int temp_point = pointer;

    if (Type()) {
        if (temp[pointer] == "id") {
            pointer++;
            std::string a = lexer.nextLexem().first;
            temp.push_back(a);
            if (!ParamListList()) {
                return false;
            }
        }
    } else{ pointer = temp_point;}
    return true;
}

bool InitVar(){
    if (temp[pointer] == "end"){
        return false;
    }

    if (temp[pointer] == "assign"){
        pointer++;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (temp[pointer] == "num") {
            pointer++;
            std::string a = lexer.nextLexem().first;
            temp.push_back(a);
            return true;
        }
        else if (temp[pointer] == "char"){
            pointer++;
            std::string a = lexer.nextLexem().first;
            temp.push_back(a);
            return true;
        }
        return false;
    }
    return true;
}

bool DeclVarList(){
    if (temp[pointer] == "end"){
        return false;
    }

    if (temp[pointer] == "comma"){
        pointer++;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (temp[pointer] == "id"){
            pointer++;
            std::string a = lexer.nextLexem().first;
            temp.push_back(a);
            if (!InitVar()){
                return false;
            }
            if (!DeclVarList()){
                return false;
            }
            return true;
        }
    }
    return true;
}

bool DeclareStmtList(){
    if (temp[pointer] == "end"){
        return false;
    }

    if (temp[pointer] == "lpar") {
        pointer++;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (!ParamList()) {
            return false;
        }
        if (temp[pointer] == "rpar") {
            pointer++;
            std::string a = lexer.nextLexem().first;
            temp.push_back(a);
            if (temp[pointer] == "lbrace") {
                pointer++;
                std::string a = lexer.nextLexem().first;
                temp.push_back(a);
                if (!StmtList()) {
                    return false;
                }
                if (temp[pointer] == "rbrace") {
                    pointer++;
                    std::string a = lexer.nextLexem().first;
                    temp.push_back(a);
                    return true;
                }
            }
        }
    }
    if (temp[pointer] == "opassign") {
        pointer++;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (temp[pointer] == "num" or temp[pointer] == "char") {
            pointer++;
            std::string a = lexer.nextLexem().first;
            temp.push_back(a);
            if (!DeclVarList()) {
                return false;
            }
            if (temp[pointer] == "semicolon") {
                return true;
            }
        }
    }
    else {
        if (!DeclVarList()){
            return false;
        }
        pointer++;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (temp[pointer] == "semicolon") {
            pointer++;
            std::string a = lexer.nextLexem().first;
            temp.push_back(a);
            return true;
        }
        return false;
    }
}

bool DeclareStmt(){
    if (temp[pointer] == "end"){
        return false;
    }

    if (!Type()){
        return false;
    }
    if (temp[pointer] != "id"){
        return false;
    }
    pointer++;
    std::string a = lexer.nextLexem().first;
    temp.push_back(a);
    if (!DeclareStmtList()){
        return false;
    }
    return true;
}

bool Type(){
    if (temp[pointer] == "end"){
        return false;
    }

    if (temp[pointer] == "kwint"){
        pointer++;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        return true;
    }
    if (temp[pointer] == "kwchar"){
        pointer++;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        return true;
    }
    return false;
}

bool Stmt() {
    if (temp[pointer] == "end"){
        return false;
    }

    int temp_point = pointer;

    if (DeclareStmt()){
        return true;
    } else {pointer = temp_point;}
    if (AssignOrCallOp()){
        return true;
    } else {pointer = temp_point;}
    if (WhileOp()){
        return true;
    } else {pointer = temp_point;}
    if (ForOp()){
        return true;
    } else {pointer = temp_point;}
//    if (IfOp()){
//        return true;
//    } else {pointer = temp_point;}
//    if (SwitchOp()){
//        return true;
//    } else {pointer = temp_point;}
//    if (IOp()){
//        return true;
//    } else {pointer = temp_point;}
//    if (OOp()){
//        return true;
//    } else {pointer = temp_point;}
    if (temp[pointer] == "semicolon"){
        pointer++;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        return true;
    }
    if (temp[pointer] == "lbrace"){
        pointer++;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (StmtList()){
            if (temp[pointer] == "rbrace"){
                pointer++;
                std::string a = lexer.nextLexem().first;
                temp.push_back(a);
                return true;
            }
        }
        return false;
    }
    if (temp[pointer] == "kwreturn"){
        pointer++;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (!E()){
            return false;
        }
        if (temp[pointer] == "semicolon") {
            pointer++;
            std::string a = lexer.nextLexem().first;
            temp.push_back(a);
            return true;
        }
        return false;
    }
    return false;

}

bool StmtList() {
    if (temp[pointer] == "end"){
        return true;
    }

    int temp_point = pointer;

    if (Stmt()){
        if (!StmtList()){
            return false;
        }
    } else {
        pointer = temp_point;
    }
    return true;
}

bool ArgList(){
    if (temp[pointer] == "id" or temp[pointer] == "num"){
        pointer++;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (temp[pointer] == "comma"){
            pointer++;
            std::string a = lexer.nextLexem().first;
            temp.push_back(a);
            if (!ArgList()){
                return false;
            }
        }
        return true;
    }
    return false;
}

bool E1_shtrih() {
    if (temp[pointer] == "opinc"){
        pointer++;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
    }
    if (temp[pointer] == "lpar"){
        pointer++;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (!ArgList()){
            return false;
        }
        if (temp[pointer] == "rpar"){
            pointer++;
            std::string a = lexer.nextLexem().first;
            temp.push_back(a);
        }
    }
    return true;
}

bool E1() {
    if (temp[pointer] == "end"){
        return false;
    }
    if (temp[pointer] == "opinc") {
        pointer++;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (temp[pointer] == "id") {
            pointer++;
            std::string a = lexer.nextLexem().first;
            temp.push_back(a);
            return true;
        }
        return false;
    }
    else if (temp[pointer] == "num") {
        pointer++;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        return true;
    }
    else if (temp[pointer] == "id") {
        pointer++;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (!E1_shtrih()){
            return false;
        }
        return true;
    }
    else if (temp[pointer] == "lpar") {
        pointer++;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (!E()) {
            return false;
        }
        if (temp[pointer] == "rpar") {
            pointer++;
            std::string a = lexer.nextLexem().first;
            temp.push_back(a);
            return true;
        }
    }
    return false;
}

bool E2() {
    if (temp[pointer] == "opnot") {
        pointer++;
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
        pointer++;
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
        pointer++;
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
        pointer++;
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
        pointer++;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (!E4()) {
            return false;
        }
    }
    else if (temp[pointer] == "opnot") {
        pointer++;
        std::string a = lexer.nextLexem().first;
        temp.push_back(a);
        if (!E4()) {
            return false;
        }
    }
    else if (temp[pointer] == "oplt") {
        pointer++;
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
        pointer++;
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
        pointer++;
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
    bool A = StmtList();
    if (A and temp[pointer] == "end"){
        std::cout << "Correct expression";
    } else {
        std::cout << "Incorrect expression";
    }

}