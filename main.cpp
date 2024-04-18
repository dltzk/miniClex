#include "lexer.h"
#include <fstream>
#include <stack>
#include <vector>
#include <iostream>
using Lexem = std::pair<std::string, std::string>;

std::fstream streamline(R"(C:\Users\Juzo Suzuya\CLionProjects\miniClex\code.txt)");
Lexer lexer(streamline);
std::vector<std::string> temp = {};
int pointer = 0;
std::vector<std::string> numbers = {};
std::vector<std::string> answer = {"StmtList"};
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
void go_back();
void new_pointer();
bool Cases();
bool ACase();
bool CasesList();

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

void string_generator(std::string expression){
    std::string temp_string = "";
    for (int i = 0; i < number_pointer; i++){
        if (numbers[i] == "0"){
            temp_string += "  ";
        } else { temp_string += "│ ";}
//        } else { temp_string += "| ";}
    }
    if (numbers[number_pointer] == "0"){
        temp_string += "└" + expression;
    } else { temp_string += "├" + expression; }
//        temp_string += "L " + expression;
//    } else { temp_string += "> " + expression; }
    answer.push_back(temp_string);
}

bool ACase(){
    if (temp[pointer] == "kwcase") {
        add_token_next();
        if (temp[pointer] == "num") {
            std::string temp_num = temp_lexem;
            add_token_next();
            if (temp[pointer] == "colon") {
                add_token_next();

                numbers.push_back("0");
                new_pointer();

                string_generator("kwcase " + temp_num + " colon StmtList");

                if (!StmtList()) {
                    return false;
                }
                go_back();
                return true;
            }
        }
    }

    if (temp[pointer] == "kwdefault") {
        add_token_next();
        if (temp[pointer] == "colon") {
            add_token_next();

            numbers.push_back("0");
            new_pointer();

            string_generator("kwdefault colon StmtList");

            if (!StmtList()) {
                return false;
            }

            go_back();
            return true;
        }
    }
    return false;
}

bool CasesList(){

    int temp_point = number_pointer;

    numbers.push_back("1");
    new_pointer();

    string_generator("ACase");

    if (ACase()){

        numbers.push_back("0");
        new_pointer();

        string_generator("CasesList");

        if (!CasesList()){
            return false;
        }

        go_back();

        return true;
    } else{
        numbers.pop_back();
        answer.pop_back();

        for (int i = 0; i < number_pointer - temp_point + 1; i++){
            go_back();
        }

        return true;
    }
}

bool Cases(){

    numbers.push_back("1");
    new_pointer();

    string_generator("ACase");

    if (!ACase()){
        return false;
    }

    numbers.push_back("0");
    new_pointer();

    string_generator("CasesList");

    if (!CasesList()) {
        return false;
    }
    go_back();
    return true;
}

bool SwitchOp(){
    if (temp[pointer] == "kwswitch"){
        add_token_next();
        if (temp[pointer] == "lpar"){
            add_token_next();

            numbers.push_back("1");
            new_pointer();

            string_generator("kwswitch lpar");

            if (!E()){
                return false;
            }
            go_back();

            if (temp[pointer] == "rpar"){
                add_token_next();
                if (temp[pointer] == "lbrace"){
                    add_token_next();

                    numbers.push_back("1");
                    new_pointer();

                    string_generator("rpar lbrace Cases");

                    if (!Cases()){
                        return false;
                    }

                    if (temp[pointer] == "rbrace"){
                        add_token_next();

                        numbers.push_back("0");
                        new_pointer();

                        string_generator("rbrace");

                        go_back();

                        go_back();

                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool ElsePart(){

    if (temp[pointer] == "kwelse"){

        add_token_next();

        numbers.push_back("0");
        new_pointer();

        string_generator("kwelse Stmt");

        if (!Stmt()){
            return false;
        }

    }

    go_back();

    return true;
}

bool IfOp(){

    numbers.push_back("0");
    new_pointer();

    string_generator("IfOp");

    if (temp[pointer] == "kwif"){

        add_token_next();

        if (temp[pointer] == "lpar"){

            numbers.push_back("1");
            new_pointer();

            string_generator("kwif lpar E");

            add_token_next();

            if (!E()){
                return false;
            }

            go_back();


            if (temp[pointer] == "rpar"){

                add_token_next();


                numbers.push_back("1");
                new_pointer();

                string_generator("rpar Stmt");

                if (!Stmt()){
                    return false;
                }
                numbers.push_back("0");
                new_pointer();

                string_generator("ElsePart");

                if (!ElsePart()){
                    return false;
                }

                go_back();

                go_back();

                return true;
            }
        }
    }
    numbers.pop_back();

    answer.pop_back();

    return false;
}

bool OOp(){
    if (temp[pointer] == "kwout"){

        numbers.push_back("0");
        new_pointer();

        string_generator("OOp");

        add_token_next();

        numbers.push_back("1");
        new_pointer();

        string_generator("kwout E");

        if (!E()){
            return false;
        }

        go_back();

        if (temp[pointer] != "semicolon"){
            return false;
        }

        add_token_next();

        numbers.push_back("0");
        new_pointer();

        string_generator("semicolon");

        go_back();

        go_back();

        go_back();

        return true;
    }
    return false;
}

bool IOp(){
    if (temp[pointer] == "kwin"){

        numbers.push_back("0");
        new_pointer();

        string_generator("IOp");


        add_token_next();


        if (temp[pointer] == "id"){

            std::string temp_id = temp_lexem;

            add_token_next();

            if (temp[pointer] != "semicolon"){
                return false;
            }

            numbers.push_back("0");
            new_pointer();

            string_generator("kwin " + temp_id + " semicolon");

            go_back();

            add_token_next();

            go_back();

            go_back();
            return true;
        }
    }
    return false;
}

bool ForLoop(){
    if (temp[pointer] == "opinc"){

        add_token_next();

        if (temp[pointer] == "id"){

            numbers.push_back("0");
            new_pointer();

            string_generator("opinc " + temp_lexem);

            add_token_next();

            go_back();

            go_back();

            return true;
        }
        return false;
    }

    numbers.push_back("1");
    new_pointer();

    string_generator("AssignOrCall");

    int temp_point = pointer;
    if (AssignOrCall()){
        go_back();
        return true;
    }
    else {
        numbers.pop_back();
        answer.pop_back();
        pointer = temp_point;
        go_back();
        return true;
    }
}

bool ForExp(){
    int temp_point = pointer;

    numbers.push_back("0");
    new_pointer();

    string_generator("E");

    int aboba = answer.size() - 1;
    int aboba_number = numbers.size() - 1;

    if (E()){

        go_back();

        go_back();

        return true;

    } else {

        answer.erase(answer.begin() + aboba, answer.end());
        numbers.erase(numbers.begin() + aboba_number, numbers.end());

        numbers.pop_back();

        pointer = temp_point;

        return true;
    }
}

bool ForInit(){
    int temp_point = pointer;

    numbers.push_back("1");
    new_pointer();

    string_generator("Type");

    if (!Type()){
        numbers.pop_back();
        answer.pop_back();
        pointer = temp_point;
    }

    numbers.push_back("0");
    new_pointer();

    string_generator("AssignOrCall");

    if (AssignOrCall()){
        go_back();
        return true;
    } else {
        numbers.pop_back();
        answer.pop_back();
        go_back();
        pointer = temp_point;
        return true;
    }
}

bool ForOp(){

    numbers.push_back("0");
    new_pointer();

    string_generator("ForOp");

    if (temp[pointer] == "kwfor"){
        add_token_next();
        if (temp[pointer] == "lpar"){
            add_token_next();

            numbers.push_back("1");
            new_pointer();

            string_generator("kwfor lpar ForInit");

            if (!ForInit()){
                return false;
            }

            if (temp[pointer] == "semicolon"){
                add_token_next();

                numbers.push_back("1");
                new_pointer();

                string_generator("semicolon ForExp");

                if (!ForExp()){
                    return false;
                }

                if (temp[pointer] == "semicolon"){
                    add_token_next();

                    numbers.push_back("1");
                    new_pointer();

                    string_generator("semicolon ForLoop");

                    if (!ForLoop()){
                        return false;
                    }

                    if (temp[pointer] == "rpar"){
                        numbers.push_back("0");
                        new_pointer();

                        string_generator("rpar Stmt");

                        add_token_next();

                        if (!Stmt()){
                            return false;
                        }

                        go_back();

                        go_back();

                        return true;
                    }

                }
            }
        }
    }
    numbers.pop_back();
    answer.pop_back();
    return false;
}

bool WhileOp(){

    numbers.push_back("0");
    new_pointer();

    string_generator("WhileOp");

    if (temp[pointer] == "kwwhile"){

        add_token_next();

        if (temp[pointer] == "lpar"){

            numbers.push_back("1");
            new_pointer();

            string_generator("kwwhile lpar E");

            add_token_next();
            if (!E()){
                return false;
            }

            go_back();

            numbers.push_back("0");
            new_pointer();

            string_generator("rpar");

            if (temp[pointer] == "rpar"){

                add_token_next();

                go_back();

                go_back();

                go_back();

                return true;
            }
        }
    }
    answer.pop_back();

    numbers.pop_back();

    return false;
}

bool AssignOrCallList(){
    if (temp[pointer] == "opassign"){

        numbers.push_back("0");
        new_pointer();

        string_generator("opassign E");

        add_token_next();

        if (!E()){
            return false;
        }
        go_back();

        go_back();
        return true;
    }
    else if (temp[pointer] == "lpar"){

        numbers.push_back("1");
        new_pointer();

        string_generator("lpar ParamList");

        add_token_next();

        if (!ParamList()){
            return false;
        }

        if (temp[pointer] == "rpar"){
            numbers.push_back("0");
            new_pointer();

            string_generator("rpar");
            add_token_next();


            go_back();

            go_back();

            return true;
        }
    }
    else{
        return false;
    }
}

bool AssignOrCall(){
    if (temp[pointer] == "id"){
        numbers.push_back("0");
        new_pointer();

        string_generator(temp_lexem + " AssignOrCallList");
        add_token_next();
        if (!AssignOrCallList()){
            return false;
        }
        go_back();
        return true;
    }
    return false;
}

bool AssignOrCallOp(){
    numbers.push_back("0");
    new_pointer();

    string_generator("AssignOrCallOp");

    numbers.push_back("1");
    new_pointer();

    string_generator("AssignOrCall");

    if (!AssignOrCall()){
        numbers.pop_back();
        numbers.pop_back();
        answer.pop_back();
        answer.pop_back();
        return false;
    }


    if (temp[pointer] != "semicolon"){
        return false;
    }
    numbers.push_back("0");
    new_pointer();

    string_generator("semicolon");

    add_token_next();

    go_back();

    go_back();

    go_back();

    return true;
}

bool ParamListList(){
    if (temp[pointer] == "end"){
        return false;
    }

    if (temp[pointer] == "comma"){

        numbers.push_back("1");
        new_pointer();

        string_generator("comma Type");

        add_token_next();

        if (!Type()){
            return false;
        }
        if (temp[pointer] == "id"){
            numbers.push_back("0");
            new_pointer();

            string_generator(temp_lexem + " ParamListList");

            add_token_next();

            if (!ParamListList()){
                return false;
            }
        }
    }
    go_back();

    return true;
}

bool ParamList() {
    if (temp[pointer] == "end") {
        return false;
    }

    int temp_point = pointer;

    numbers.push_back("1");
    new_pointer();

    string_generator("Type");

    if (Type()) {
        if (temp[pointer] == "id") {
            numbers.push_back("0");
            new_pointer();

            string_generator(temp_lexem + " ParamListList");

            add_token_next();
            if (!ParamListList()) {
                return false;
            }
        }
    } else{
        answer.pop_back();
        numbers.pop_back();
        pointer = temp_point;
        go_back();
    }

    go_back();
    return true;
}

bool InitVar(){
    if (temp[pointer] == "end"){
        return false;
    }

    if (temp[pointer] == "opassign"){
        add_token_next();
        if (temp[pointer] == "num") {

            numbers.push_back("0");
            new_pointer();

            string_generator("opassign " + temp_lexem);

            add_token_next();

            go_back();

            go_back();

            return true;
        }
        else if (temp[pointer] == "char"){
            numbers.push_back("0");
            new_pointer();

            string_generator(temp_lexem);

            add_token_next();

            go_back();

            go_back();

            return true;
        }
        return false;
    }
    go_back();
    return true;
}

bool DeclVarList(){

    if (temp[pointer] == "end"){
        return false;
    }

    if (temp[pointer] == "comma"){

        add_token_next();

        if (temp[pointer] == "id"){

            numbers.push_back("1");
            new_pointer();

            string_generator("comma " + temp_lexem + " InitVar");

            add_token_next();

            if (!InitVar()){
                return false;
            }

            numbers.push_back("0");
            new_pointer();

            string_generator("DeclVarList");


            if (!DeclVarList()){
                return false;
            }
        }
    }

    go_back();
    return true;
}

bool DeclareStmtList(){
    if (temp[pointer] == "end"){
        return false;
    }


    if (temp[pointer] == "lpar") {

        add_token_next();

        numbers.push_back("1");
        new_pointer();

        string_generator("lpar ParamList");

        if (!ParamList()) {
            return false;
        }


        if (temp[pointer] == "rpar") {

            add_token_next();

            if (temp[pointer] == "lbrace") {
                numbers.push_back("1");
                new_pointer();

                string_generator("rpar lbrace StmtList");

                add_token_next();

                if (!StmtList()) {
                    return false;
                }
                if (temp[pointer] == "rbrace") {
                    numbers.push_back("0");
                    new_pointer();

                    string_generator("rbrace");
                    add_token_next();

                    go_back();

                    go_back();
                    return true;
                }
            }
        }
    }
    if (temp[pointer] == "opassign") {

        add_token_next();

        if (temp[pointer] == "num" or temp[pointer] == "char") {

            numbers.push_back("1");
            new_pointer();

            string_generator("opassign " + temp_lexem + " DeclVarList");

            add_token_next();

            if (!DeclVarList()) {
                return false;
            }

            if (temp[pointer] == "semicolon") {
                numbers.push_back("0");
                new_pointer();

                string_generator("semicolon");

                add_token_next();

                go_back();

                go_back();

                return true;
            }
        }
    }
    else {

        numbers.push_back("1");
        new_pointer();

        string_generator("DeclVarList");

        if (!DeclVarList()){
            return false;
        }

        if (temp[pointer] == "semicolon") {
            numbers.push_back("0");
            new_pointer();

            string_generator("semicolon");

            add_token_next();

            go_back();

            go_back();

            return true;
        }
        return false;
    }
}

bool DeclareStmt(){
    if (temp[pointer] == "end"){
        return false;
    }

    numbers.push_back("0");
    new_pointer();

    string_generator("DeclareStmt");

    numbers.push_back("1");
    new_pointer();

    string_generator("Type");

    if (!Type()){
        numbers.pop_back();
        numbers.pop_back();
        answer.pop_back();
        answer.pop_back();
        return false;
    }

    if (temp[pointer] != "id"){
        return false;
    }
    numbers.push_back("0");
    new_pointer();

    string_generator(temp_lexem + " DeclareStmtList");

    add_token_next();
    if (!DeclareStmtList()){
        return false;
    }
    go_back();

    go_back();
    return true;
}

bool Type(){
    if (temp[pointer] == "end"){
        return false;
    }

    if (temp[pointer] == "kwint"){
        add_token_next();

        numbers.push_back("0");
        new_pointer();

        string_generator("kwint");

        go_back();

        go_back();

        return true;
    }
    if (temp[pointer] == "kwchar"){
        add_token_next();

        numbers.push_back("0");
        new_pointer();

        string_generator("kwchar");

        go_back();

        go_back();

        return true;
    }
    return false;
}

bool Stmt() {
    if (temp[pointer] == "end"){
        return false;
    }

    int temp_point = pointer;

    int temp_number = number_pointer;

    if (DeclareStmt()){
        return true;
    } else {
        number_pointer = temp_number;
        pointer = temp_point;}
    if (AssignOrCallOp()){
        return true;
    } else {
        number_pointer = temp_number;
        pointer = temp_point;}
    if (WhileOp()){
        return true;
    } else {
        number_pointer = temp_number;
        pointer = temp_point;}
    if (ForOp()){
        return true;
    } else {pointer = temp_point;}
    if (IfOp()){
        return true;
    } else {pointer = temp_point;}
    if (SwitchOp()){
        return true;
    } else {pointer = temp_point;}
    if (IOp()){
        return true;
    } else {pointer = temp_point;}
    if (OOp()){
        return true;
    } else {pointer = temp_point;}

    if (temp[pointer] == "semicolon"){

        numbers.push_back("0");
        new_pointer();

        string_generator("semicolon");

        add_token_next();

        go_back();

        go_back();

        return true;

    }
    if (temp[pointer] == "lbrace"){

        numbers.push_back("1");
        new_pointer();

        string_generator("lbrace");

        add_token_next();

        numbers.push_back("0");
        new_pointer();

        string_generator("StmtList");


        if (StmtList()){

            go_back();

            if (temp[pointer] == "rbrace"){


                numbers.push_back("0");
                new_pointer();

                string_generator("rbrace");

                add_token_next();

                go_back();

                go_back();

                return true;
            }
        }
        return false;
    }
    if (temp[pointer] == "kwreturn"){
        add_token_next();

        numbers.push_back("1");
        new_pointer();

        string_generator("kwreturn E");


        if (!E()){
            return false;
        }

        go_back();


        if (temp[pointer] == "semicolon") {
            add_token_next();

            numbers.push_back("0");
            new_pointer();

            string_generator("semicolon");

            go_back();

            go_back();

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

    numbers.push_back("1");
    new_pointer();

    string_generator("Stmt");

    if (Stmt()){
        numbers.push_back("0");
        new_pointer();

        string_generator("StmtList");

        if (!StmtList()){
            return false;
        }
    } else {
        answer.pop_back();
        numbers.pop_back();
        pointer = temp_point;
    }
    go_back();
    return true;
}

bool ArgList(){
    if (temp[pointer] == "id"){

//        std::string temp_id = temp_lexem;

//        numbers.push_back("1");
//        new_pointer();
//
//        string_generator(temp_lexem);
//
//        add_token_next();
//
        std::string temp_id = temp_lexem;

        add_token_next();

        if (temp[pointer] == "comma"){
            numbers.push_back("1");
            new_pointer();
            string_generator(temp_id);
        } else {
            numbers.push_back("0");
            new_pointer();
            string_generator(temp_id);
        }


        if (temp[pointer] == "comma"){

            add_token_next();

            go_back();

            numbers.push_back("0");
            new_pointer();

            string_generator("comma ArgList");

            int point = number_pointer;


            if (!ArgList()){
                numbers.erase(numbers.begin() + point, numbers.begin() + number_pointer);
                return false;
            }
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

        string_generator("opinc");

        go_back();
    }
    else if (temp[pointer] == "lpar"){
        add_token_next();

        numbers.push_back("1");
        new_pointer();

        string_generator("lpar ArgList");

        if (!ArgList()){
            numbers.erase(numbers.begin() + point, numbers.begin() + number_pointer);
            return false;
        }
        go_back();

        point = number_pointer;

        if (temp[pointer] == "rpar"){
            add_token_next();

            numbers.push_back("0");
            new_pointer();

            string_generator("rpar");

            go_back();


        } else {
            return false;
        }
    }
    go_back();
    return true;
}

bool E1() {
    int point = number_pointer;
    if (temp[pointer] == "opinc") {
        add_token_next();

        numbers.push_back("0");
        new_pointer();

        string_generator("opinc");


        if (temp[pointer] == "id") {

            numbers.push_back("0");
            new_pointer();

            string_generator(temp_lexem);

            add_token_next();

            go_back();
            go_back();
            go_back();
            return true;
        }
        return false;
    }
    else if (temp[pointer] == "num") {

        numbers.push_back("0");
        new_pointer();

        string_generator(temp_lexem);

        add_token_next();

        go_back();
        go_back();
        return true;
    }
    else if (temp[pointer] == "id") {

        numbers.push_back("0");
        new_pointer();

        string_generator(temp_lexem + " E1List");

        add_token_next();

        if (!E1_shtrih()){
            return false;
        }
        go_back();
        return true;
    }
    else if (temp[pointer] == "lpar") {
        add_token_next();

        numbers.push_back("1");
        new_pointer();

        string_generator("lpar E");

        if (!E()) {
            return false;
        }
        go_back();

        if (temp[pointer] == "rpar") {
            add_token_next();

            numbers.push_back("0");
            new_pointer();

            string_generator("rpar");

            go_back();
            go_back();
            return true;
        }
    }
    return false;
}

bool E2() {
    int point = number_pointer;
    if (temp[pointer] == "opnot") {
        add_token_next();

        numbers.push_back("0");
        new_pointer();

        string_generator("opnot E1");

        if (!E1()){
            return false;
        }


    } else {
        numbers.push_back("0");
        new_pointer();

        string_generator("E1");

        if (!E1()) {
            return false;
        }
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

        string_generator("opmul E2");

        if (!E2()) {
            return false;
        }

        point = number_pointer;

        numbers.push_back("0");
        new_pointer();

        string_generator("E3List");

        if (!E3_shtrih()) {
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

    string_generator("E2");

    if (!E2()) {
        return false;
    }

    point = number_pointer;

    numbers.push_back("0");
    new_pointer();

    string_generator("E3List");

    if (!E3_shtrih()){
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

        string_generator("opplus E3");

        if (!E3()) {
            return false;
        }

        point = number_pointer;

        numbers.push_back("0");
        new_pointer();

        string_generator("E4List");

        if (!E4_shtrih()) {
            return false;
        }
    }
    else if (temp[pointer] == "opminus") {
        add_token_next();

        int point = number_pointer;

        numbers.push_back("1");
        new_pointer();

        string_generator("opminus E3");

        if (!E3()) {
            return false;
        }
        point = number_pointer;

        numbers.push_back("0");
        new_pointer();

        string_generator("E4List");

        if (!E4_shtrih()) {
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

    string_generator("E3");

    if (!E3()) {
        return false;
    }

    point = number_pointer;

    numbers.push_back("0");
    new_pointer();

    string_generator("E4List");

    if (!E4_shtrih()){
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

        string_generator("opeq E4");

        if (!E4()) {
            return false;
        }
    }
    else if (temp[pointer] == "opne") {
        add_token_next();

        int point = number_pointer;

        numbers.push_back("0");
        new_pointer();

        string_generator("opne E4");

        if (!E4()) {
            return false;
        }
    }
    else if (temp[pointer] == "oplt") {
        add_token_next();

        int point = number_pointer;

        numbers.push_back("0");
        new_pointer();

        string_generator("oplt E4");

        if (!E4()) {
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

    string_generator("E4");

    if (!E4()) {
        return false;
    }

    point = number_pointer;

    numbers.push_back("0");
    new_pointer();

    string_generator("E5List");

    if (!E5_shtrih()) {
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

        string_generator("opand E5");

        if (!E5()) {
            return false;
        }

        point = number_pointer;

        numbers.push_back("0");
        new_pointer();

        string_generator("E6List");

        if (!E6_shtrih()) {
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

    string_generator("E5");


    if (!E5()) {
        return false;
    }

    point = number_pointer;

    numbers.push_back("0");
    new_pointer();

    string_generator("E6List");

    if (!E6_shtrih()) {
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

        string_generator("opor E6");

        if (!E6()) {
            return false;
        }

        point = number_pointer;

        numbers.push_back("0");
        new_pointer();

        string_generator("E7List");

        if (!E7_shtrih()) {
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

    string_generator("E6");

    if (!E6()){
        return false;
    }

    point = number_pointer;

    numbers.push_back("0");
    new_pointer();

    string_generator("E7List");

    if (!E7_shtrih()) {
        return false;
    }
    go_back();
    return true;
}

bool E() {
    int point = number_pointer;
    std::cout << number_pointer << std::endl;
    numbers.push_back("0");
    new_pointer();

    string_generator("E7");

    if (!E7()) {
        return false;
    }

    return true;
}

int main() {
    Lexem lexem;
    std::ofstream output;
    lexem = lexer.nextLexem();
    std::string a = lexem.first;
    temp_lexem = lexem.second;
    temp.push_back(a);
    bool A = StmtList();
    output.open(R"(C:\Users\Juzo Suzuya\CLionProjects\miniClex\output.txt)");
    for (auto i = answer.begin(); i != answer.end(); i++){
        output << *i << std::endl;
    }
    output.close();
    streamline.close();
    if (A and temp[pointer] == "end"){
        std::cout << "Correct expression";
    } else {
        std::cout << "Incorrect expression";
    }
    return 0;
}