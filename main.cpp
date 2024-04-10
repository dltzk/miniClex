#include "lexer.h"
#include <fstream>
#include <stack>
#include <vector>
#include <iostream>

using Lexem = std::pair<std::string, std::string>;
std::fstream streamline(R"(C:\Users\Juzo Suzuya\CLionProjects\miniClex\code.txt)");
std::ofstream output;
Lexer lexer(streamline);
std::vector<std::string> temp = {};
int pointer = 0;
std::vector<std::string> numbers = {};
std::vector<std::string> answer = {"E"};
int number_pointer = 0;
std::string temp_lexem = "";
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
bool ElsePart();
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
void add_token_next();

void new_pointer(){
    number_pointer = numbers.size() - 1;
}

void go_back(){
    number_pointer--;
    numbers.pop_back();
}

void add_token_next(){
    Lexem lexem_for_output;
    lexem_for_output = lexer.nextLexem();
    pointer++;
    std::string a = lexem_for_output.first;
    temp_lexem = lexem_for_output.second;
    temp.push_back(a);
}

std::string substring_generator(){
    std::string temp_string = "";
    for (int i = 0; i < number_pointer; i++){
        if (numbers[i] == "0"){
            temp_string += "  ";
        } else { temp_string += "│ ";}
    }
    if (numbers[number_pointer] == "0"){
        temp_string += "└";
    } else { temp_string += "├";}
    return temp_string;
}

bool ElsePart(){
    if (temp[pointer] == "kwelse"){
        add_token_next();
        if (!Stmt()){
            return false;
        }
    }
    return true;
}

bool IfOp(){
    if (temp[pointer] == "kwif"){
        add_token_next();
        if (temp[pointer] == "lpar"){
            add_token_next();
            if (!E()){
                return false;
            }
            if (temp[pointer] == "rpar"){
                add_token_next();
                if (!Stmt()){
                    return false;
                }
                if (!ElsePart()){
                    return false;
                }
                return true;
            }
        }
    }
    return false;
}

bool OOp(){
    if (temp[pointer] == "kwout"){
        add_token_next();
        if (!E()){
            return false;
        }
        if (temp[pointer] != "semicolon"){
            return false;
        }
        return true;
    }
    return false;
}

bool IOp(){
    if (temp[pointer] == "kwin"){
        add_token_next();
        if (temp[pointer] == "id"){
            add_token_next();
            if (temp[pointer] != "semicolon"){
                return false;
            }
            return true;
        }
    }
    return false;
}

bool ForLoop(){
    if (temp[pointer] == "opinc"){
        add_token_next();
        if (temp[pointer] == "id"){
            add_token_next();
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
    if (!Type()){
        pointer = temp_point;
    }
    if (AssignOrCall()){
        return true;
    } else {
        pointer = temp_point;
        return true;
    }
}

bool ForOp(){
    if (temp[pointer] == "kwfor"){
        add_token_next();
        if (temp[pointer] == "lpar"){
            add_token_next();
            if (!ForInit()){
                return false;
            }
            if (temp[pointer] == "semicolon"){
                add_token_next();
                if (!ForExp()){
                    return false;
                }
                if (temp[pointer] == "semicolon"){
                    add_token_next();
                    if (!ForLoop()){
                        return false;
                    }
                    if (temp[pointer] == "rpar"){
                        add_token_next();
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
        add_token_next();
        if (temp[pointer] == "lpar"){
            add_token_next();
            if (!E()){
                return false;
            }
            if (temp[pointer] == "rpar"){
                add_token_next();
                return true;
            }
        }
    }
    return false;
}

bool AssignOrCallList(){
    if (temp[pointer] == "opassign"){
        add_token_next();
        if (!E()){
            return false;
        }
        return true;
    }
    else if (temp[pointer] == "lpar"){
        add_token_next();
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
        add_token_next();
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
    add_token_next();
    return true;
}

bool ParamListList(){
    if (temp[pointer] == "end"){
        return false;
    }

    if (temp[pointer] == "comma"){
        add_token_next();
        if (!Type()){
            return false;
        }
        if (temp[pointer] == "id"){
            add_token_next();
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
            add_token_next();
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

    if (temp[pointer] == "opassign"){
        add_token_next();
        if (temp[pointer] == "num") {
            add_token_next();
            return true;
        }
        else if (temp[pointer] == "char"){
            add_token_next();
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
        add_token_next();
        if (temp[pointer] == "id"){
            add_token_next();
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
        add_token_next();
        if (!ParamList()) {
            return false;
        }
        if (temp[pointer] == "rpar") {
            add_token_next();
            if (temp[pointer] == "lbrace") {
                add_token_next();
                if (!StmtList()) {
                    return false;
                }
                if (temp[pointer] == "rbrace") {
                    add_token_next();
                    return true;
                }
            }
        }
    }
    if (temp[pointer] == "opassign") {
        add_token_next();
        if (temp[pointer] == "num" or temp[pointer] == "char") {
            add_token_next();
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
        if (temp[pointer] == "semicolon") {
            add_token_next();
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
    add_token_next();
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
        add_token_next();
        return true;
    }
    if (temp[pointer] == "kwchar"){
        add_token_next();
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
    if (IfOp()){
        return true;
    } else {pointer = temp_point;}
//    if (SwitchOp()){
//        return true;
//    } else {pointer = temp_point;}
    if (IOp()){
        return true;
    } else {pointer = temp_point;}
    if (OOp()){
        return true;
    } else {pointer = temp_point;}
    if (temp[pointer] == "semicolon"){
        add_token_next();
        return true;
    }
    if (temp[pointer] == "lbrace"){
        add_token_next();
        if (StmtList()){
            if (temp[pointer] == "rbrace"){
                add_token_next();
                return true;
            }
        }
        return false;
    }
    if (temp[pointer] == "kwreturn"){
        add_token_next();
        if (!E()){
            return false;
        }
        if (temp[pointer] == "semicolon") {
            add_token_next();
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
    if (temp[pointer] == "id"){

        numbers.push_back("0");
        new_pointer();

        std::string temp_string = substring_generator() + temp_lexem;
        answer.push_back(temp_string);

        add_token_next();

        if (temp[pointer] == "comma"){


            add_token_next();

            numbers.push_back("1");
            new_pointer();


            std::string temp_string = substring_generator() + "comma ArgList";
            answer.push_back(temp_string);

            go_back();

            int point = number_pointer;

            if (!ArgList()){
                numbers.erase(numbers.begin() + point, numbers.begin() + number_pointer);
                return false;
            }
            go_back();
        }
    }
    go_back();
    return true;
}

bool E1_shtrih() {
    int point = number_pointer;
    if (temp[pointer] == "opinc"){
        add_token_next();

        numbers.push_back("0");
        new_pointer();

        std::string temp_string = substring_generator() + "opinc";
        answer.push_back(temp_string);
        go_back();
    }
    else if (temp[pointer] == "lpar"){
        add_token_next();

        numbers.push_back("1");
        new_pointer();

        std::string temp_string = substring_generator() + "lpar ArgList";
        answer.push_back(temp_string);

        if (!ArgList()){
            numbers.erase(numbers.begin() + point, numbers.begin() + number_pointer);
            return false;
        }

        point = number_pointer;

        if (temp[pointer] == "rpar"){
            add_token_next();

            numbers.push_back("0");
            new_pointer();

            std::string temp_string1 = substring_generator() + "rpar";
            answer.push_back(temp_string1);
            go_back();
        } else {
            numbers.erase(numbers.begin() + point, numbers.begin() + number_pointer);
            return false;
        }
    }

    return true;
}

bool E1() {
    int point = number_pointer;
    if (temp[pointer] == "opinc") {
        add_token_next();

        numbers.push_back("1");
        new_pointer();

        std::string temp_string = substring_generator() + "opinc";
        answer.push_back(temp_string);



        if (temp[pointer] == "id") {

            numbers.push_back("0");
            new_pointer();

            std::string temp_string = substring_generator() + temp_lexem;
            answer.push_back(temp_string);

            add_token_next();

            return true;
        }
        numbers.erase(numbers.begin() + point, numbers.begin() + number_pointer);
        return false;
    }
    else if (temp[pointer] == "num") {

        numbers.push_back("0");
        new_pointer();

        std::string temp_string = substring_generator() + temp_lexem;
        answer.push_back(temp_string);

        add_token_next();

        go_back();
        return true;
    }
    else if (temp[pointer] == "id") {

        numbers.push_back("0");
        new_pointer();

        std::string temp_string = substring_generator() + temp_lexem;
        answer.push_back(temp_string);

        add_token_next();

        if (!E1_shtrih()){
            numbers.erase(numbers.begin() + point, numbers.begin() + number_pointer);
            return false;
        }
        go_back();
        return true;
    }
    else if (temp[pointer] == "lpar") {
        add_token_next();

        numbers.push_back("1");
        new_pointer();

        std::string temp_string = substring_generator() + "lpar E";
        answer.push_back(temp_string);

        if (!E()) {
            numbers.erase(numbers.begin() + point, numbers.begin() + number_pointer);
            return false;
        }

        if (temp[pointer] == "rpar") {
            add_token_next();

            numbers.push_back("0");
            new_pointer();

            std::string temp_string = substring_generator() + "rpar";
            answer.push_back(temp_string);

            go_back();

            return true;
        }
    }
    numbers.erase(numbers.begin() + point, numbers.begin() + number_pointer);
    return false;
}

bool E2() {
    int point = number_pointer;
    if (temp[pointer] == "opnot") {
        add_token_next();

        numbers.push_back("0");
        new_pointer();

        std::string temp_string = substring_generator() + "opnot E1";
        answer.push_back(temp_string);

        if (!E1()){
            numbers.erase(numbers.begin() + point, numbers.begin() + number_pointer);
            return false;
        }

        go_back();

    } else {
        numbers.push_back("0");
        new_pointer();

        std::string temp_string = substring_generator() + "E1";
        answer.push_back(temp_string);

        if (!E1()) {
            numbers.erase(numbers.begin() + point, numbers.begin() + number_pointer);
            return false;
        }
        go_back();
    }
    go_back();
    return true;
}

bool E3_shtrih() {
    if (temp[pointer] == "opmul") {
        add_token_next();

        int point = number_pointer;

        numbers.push_back("1");
        new_pointer();

        std::string temp_string = substring_generator() + "opmul E2";
        answer.push_back(temp_string);

        if (!E2()) {
            answer.erase(answer.begin() + point, answer.begin() + number_pointer);
            return false;
        }

        point = number_pointer;

        numbers.push_back("0");
        new_pointer();

        std::string temp_string1 = substring_generator() + "E3List";
        answer.push_back(temp_string1);

        if (!E3_shtrih()) {
            answer.erase(answer.begin() + point, answer.begin() + number_pointer);
            return false;
        }
    }
    go_back();
    return true;
}

bool E3() {
    int point = number_pointer;

    numbers.push_back("1");
    new_pointer();

    std::string temp_string = substring_generator() + "E2";
    answer.push_back(temp_string);

    if (!E2()) {
        answer.erase(answer.begin() + point, answer.begin() + number_pointer);
        return false;
    }

    point = number_pointer;

    numbers.push_back("0");
    new_pointer();

    std::string temp_string1 = substring_generator() + "E3List";
    answer.push_back(temp_string1);

    if (!E3_shtrih()){
        answer.erase(answer.begin() + point, answer.begin() + number_pointer);
        return false;
    }
    go_back();
    return true;
}

bool E4_shtrih() {
    if (temp[pointer] == "opplus") {
        add_token_next();

        int point = number_pointer;

        numbers.push_back("1");
        new_pointer();

        std::string temp_string = substring_generator() + "opplus E3";
        answer.push_back(temp_string);

        if (!E3()) {
            answer.erase(answer.begin() + point, answer.begin() + number_pointer);
            return false;
        }

        point = number_pointer;

        numbers.push_back("0");
        new_pointer();

        std::string temp_string1 = substring_generator() + "E4List";
        answer.push_back(temp_string1);

        if (!E4_shtrih()) {
            answer.erase(answer.begin() + point, answer.begin() + number_pointer);
            return false;
        }
    }
    else if (temp[pointer] == "opminus") {
        add_token_next();

        int point = number_pointer;

        numbers.push_back("1");
        new_pointer();

        std::string temp_string = substring_generator() + "opminus E3";
        answer.push_back(temp_string);

        if (!E3()) {
            answer.erase(answer.begin() + point, answer.begin() + number_pointer);
            return false;
        }
        point = number_pointer;

        numbers.push_back("0");
        new_pointer();

        std::string temp_string1 = substring_generator() + "E4List";
        answer.push_back(temp_string1);

        if (!E4_shtrih()) {
            answer.erase(answer.begin() + point, answer.begin() + number_pointer);
            return false;
        }
    }
    go_back();
    return true;
}

bool E4() {
    int point = number_pointer;

    numbers.push_back("1");
    new_pointer();

    std::string temp_string = substring_generator() + "E3";
    answer.push_back(temp_string);

    if (!E3()) {
        answer.erase(answer.begin() + point, answer.begin() + number_pointer);
        return false;
    }

    point = number_pointer;

    numbers.push_back("0");
    new_pointer();

    std::string temp_string1 = substring_generator() + "E4List";
    answer.push_back(temp_string1);

    if (!E4_shtrih()){
        answer.erase(answer.begin() + point, answer.begin() + number_pointer);
        return false;
    }

    go_back();
    return true;
}

bool E5_shtrih() {
    if (temp[pointer] == "opeq") {
        add_token_next();

        int point = number_pointer;

        numbers.push_back("0");
        new_pointer();

        std::string temp_string = substring_generator() + "opeq E4";
        answer.push_back(temp_string);

        if (!E4()) {
            answer.erase(answer.begin() + point, answer.begin() + number_pointer);
            return false;
        }
    }
    else if (temp[pointer] == "opne") {
        add_token_next();

        int point = number_pointer;

        numbers.push_back("0");
        new_pointer();

        std::string temp_string = substring_generator() + "opne E4";
        answer.push_back(temp_string);

        if (!E4()) {
            answer.erase(answer.begin() + point, answer.begin() + number_pointer);
            return false;
        }
    }
    else if (temp[pointer] == "oplt") {
        add_token_next();

        int point = number_pointer;

        numbers.push_back("0");
        new_pointer();

        std::string temp_string = substring_generator() + "oplt E4";
        answer.push_back(temp_string);

        if (!E4()) {
            answer.erase(answer.begin() + point, answer.begin() + number_pointer);
            return false;
        }
    }
    go_back();
    return true;
}

bool E5() {
    int point = number_pointer;

    numbers.push_back("1");
    new_pointer();

    std::string temp_string = substring_generator() + "E4";
    answer.push_back(temp_string);

    if (!E4()) {
        answer.erase(answer.begin() + point, answer.begin() + number_pointer);
        return false;
    }

    point = number_pointer;

    numbers.push_back("0");
    new_pointer();

    std::string temp_string2 = substring_generator() + "E5List";
    answer.push_back(temp_string2);

    if (!E5_shtrih()) {
        answer.erase(answer.begin() + point, answer.begin() + number_pointer);
        return false;
    }

    go_back();
    return true;
}


bool E6_shtrih() {
    if (temp[pointer] == "opand") {
        add_token_next();

        int point = number_pointer;

        numbers.push_back("1");
        new_pointer();

        std::string temp_string = substring_generator() + "opand E5";
        answer.push_back(temp_string);

        if (!E5()) {
            answer.erase(answer.begin() + point, answer.begin() + number_pointer);
            return false;
        }
        point = number_pointer;

        numbers.push_back("0");
        new_pointer();

        std::string temp_string1 = substring_generator() + "E6List";
        answer.push_back(temp_string1);

        if (!E6_shtrih()) {
            answer.erase(answer.begin() + point, answer.begin() + number_pointer);
            return false;
        }
    }
    go_back();
    return true;
}

bool E6() {
    int point = number_pointer;

    numbers.push_back("1");
    new_pointer();

    std::string temp_string = substring_generator() + "E5";
    answer.push_back(temp_string);


    if (!E5()) {
        answer.erase(answer.begin() + point, answer.begin() + number_pointer);
        return false;
    }

    point = number_pointer;

    numbers.push_back("0");
    new_pointer();

    std::string temp_string1 = substring_generator() + "E6List";
    answer.push_back(temp_string1);

    if (!E6_shtrih()) {
        answer.erase(answer.begin() + point, answer.begin() + number_pointer);
        return false;
    }
    go_back();
    return true;
}

bool E7_shtrih() {
    if (temp[pointer] == "opor") {

        add_token_next();

        int point = number_pointer;

        numbers.push_back("1");
        new_pointer();

        std::string temp_string = substring_generator() + "opor E6";
        answer.push_back(temp_string);

        if (!E6()) {
            answer.erase(answer.begin() + point, answer.begin() + number_pointer);
            return false;
        }

        point = number_pointer;

        numbers.push_back("0");
        new_pointer();

        std::string temp_string1 = substring_generator() + "E7List";
        answer.push_back(temp_string1);

        if (!E7_shtrih()) {
            answer.erase(answer.begin() + point, answer.begin() + number_pointer);
            return false;
        }
    }
    go_back();
    return true;
}

bool E7() {
    int point = number_pointer;

    numbers.push_back("1");
    new_pointer();

    std::string temp_string = substring_generator() + "E6";
    answer.push_back(temp_string);

    if (!E6()){
        answer.erase(answer.begin() + point, answer.begin() + number_pointer);
        return false;
    }

    point = number_pointer;

    numbers.push_back("0");
    new_pointer();

    std::string temp_string1 = substring_generator() + "E7List";
    answer.push_back(temp_string1);

    if (!E7_shtrih()) {
        answer.erase(answer.begin() + point, answer.begin() + number_pointer);
        return false;
    }

    go_back();
    return true;
}

bool E() {
    int point = number_pointer;
    numbers.push_back("0");
    new_pointer();

    std::string temp_string = substring_generator() + "E7";
    answer.push_back(temp_string);

    if (!E7()) {
        answer.erase(answer.begin() + point, answer.begin() + number_pointer);
        return false;
    }
    go_back();
    return true;
}

int main() {
    Lexem lexem;
    lexem = lexer.nextLexem();
    std::string a = lexem.first;
    temp_lexem = lexem.second;
    temp.push_back(a);
    bool A = E();
    output.open(R"(C:\Users\Juzo Suzuya\CLionProjects\miniClex\output.txt)");
    while (!answer.empty()) {
        output << answer.front() << std::endl;
        answer.erase(answer.begin());
    }
    output.close();
    if (A and temp[pointer] == "end"){
        std::cout << "Correct expression";
    } else {
        std::cout << "Incorrect expression";
    }
}