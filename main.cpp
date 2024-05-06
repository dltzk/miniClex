#include "lexer.h"
#include <fstream>
#include <stack>
#include <vector>
#include <iostream>
#include "ll.h"
#include <map>

using Lexem = std::pair<std::string, std::string>;
using bd = std::pair<bool, std::string>;

std::ofstream tree;
std::ofstream atoms;
std::fstream streamline(R"(C:\Users\Juzo Suzuya\CLionProjects\miniClex\code.txt)");
Lexer lexer(streamline);
std::vector<std::string> temp = {};
int pointer = 0;
std::vector<std::string> numbers = {};
std::vector<std::string> answer = {"StmtList"};
int number_pointer = 0;
std::string temp_lexem = "";
std::vector<Atom> Atoms = {};
std::vector<Params> sortedAtoms = {};
std::vector<std::string> contexts = {"-1"};
std::map<std::string, std::vector<Params>> AtomsMap = {};
int LabelCounter = 0;
int AtomsMapCounter = 0;
int NewVariableCounter = 0;

bd E();
bd E1();
bd E2();
bd E3();
bd E4();
bd E5();
bd E6();
bd E7();
bd E7_shtrih();
bd E6_shtrih();
bd E5_shtrih();
bd E4_shtrih();
bd E3_shtrih();
bd E1_shtrih();
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
bd Type();
bd ParamList();
bd ParamListList();
bool DeclVarList();
bool InitVar();
bool AssignOrCall();
bool AssignOrCallOp();
bool AssignOrCallList();
bool ForInit();
bool ForExp();
bool ForLoop();
bd ArgList();
void add_token_next();
void go_back();
void new_pointer();
bool Cases();
bool ACase();
bool CasesList();

std::string addVar(std::string name, std::string scope, std::string type, std::string init);
std::string addFunc(std::string name, std::string type, std::string len);
std::string alloc();
std::string newLabel();
std::string checkVar(std::string name);
std::string checkFunc(std::string scope, std::string name);
void print_tree();
void print_atoms();
void generate_atom(std::string context, std::string name, std::string first, std::string second, std::string third);

void generate_atom(std::string context = "", std::string name = "", std::string first = "", std::string second = "", std::string third = ""){
    if (context == "error" or name == "error" or first == "error" or second == "error" or third == "error") {
        Atom Atom = {"error", "error", "error", "error", "error"};
        Atoms.push_back(Atom);
        return;
    }
    Atom Atom = {context, name, first, second, third};
    Atoms.push_back(Atom);
    return;
}

void print_atoms(){
    atoms.open(R"(C:\Users\Juzo Suzuya\CLionProjects\miniClex\atoms.txt)");
    for (auto i: Atoms){
        atoms << i.context << ": " << "(" << i.name << "," << i.first << "," << i.second << "," << i.third << ")" << std::endl;
    }
    atoms << std::endl;

    atoms << "name" << " " << "scope" << " " << "type" << " " << "init" << " " << "kind" << " " << "id" << " " << "len" << std::endl;
    atoms << std::endl;
    for (auto i: AtomsMap){
        for (auto j: i.second) {

            atoms << j.name << " " << j.scope << " " << j.type << " " << j.init << " " << " " << j.kind << " "
                  << j.number_of_id << " " << j.len << std::endl;
        }
    }
    atoms.close();
}

void print_tree(){
    tree.open(R"(C:\Users\Juzo Suzuya\CLionProjects\miniClex\tree.txt)");
    for (auto i = answer.begin(); i != answer.end(); i++){
        tree << *i << std::endl;
    }
    tree.close();
}

std::string newLabel() {
    std::string labelMark = std::to_string(LabelCounter++);
    return labelMark;
}

std::string alloc(std::string scope) {
    std::string name = std::to_string(NewVariableCounter++);
    std::string temp = addVar("$TEMP_" + name, scope, "kwint", "0");
    return temp;
}

std::string checkVar(std::string name){
    auto context = contexts.rbegin();

    while (context != contexts.rend()) {
        for (auto &a: AtomsMap[*context]) {
            if (a.name == name and a.kind == "var") {
                std::string temp = std::to_string(a.number_of_id);
                return temp;
            } else if (a.name == name and a.kind != "var") { return "error"; }
        }
        context++;
    }
    return "error";
}

std::string checkFunc(std::string name, std::string len){
    for (auto &a: AtomsMap["-1"]){
        if (a.name == name and a.kind == "func" and a.init == len) {
            std::string temp = std::to_string(a.number_of_id);
            return temp;
        } else if (a.name == name and a.kind != "func"){ return "error";}
    }
    return "error";
}

std::string addVar(std::string name, std::string scope, std::string type, std::string init){
    if (AtomsMap.count(scope)){
        for (auto &a: AtomsMap[scope]){
            if (a.name == name){
                return "error";
            }
        }
    }

    Params text = {name, scope, type, init, "var", "-", AtomsMapCounter++};
    AtomsMap[scope].push_back(text);
    std::string temp = std::to_string(text.number_of_id);
    return temp;
}

std::string addFunc(std::string name, std::string type, std::string len) {
    for (auto &a: AtomsMap["-1"]) {
        if (a.name == name) {
            return "error";
        }
    }
    Params text = {name, "-1", type, "-", "func", len, AtomsMapCounter++};
    AtomsMap["-1"].push_back(text);
    std::string temp = std::to_string(text.number_of_id);
    return temp;
}

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

//bool ACase(){
//    if (temp[pointer] == "kwcase") {
//        add_token_next();
//        if (temp[pointer] == "num") {
//            std::string temp_num = temp_lexem;
//            add_token_next();
//            if (temp[pointer] == "colon") {
//                add_token_next();
//
//                numbers.push_back("0");
//                new_pointer();
//
//                string_generator("kwcase " + temp_num + " colon StmtList");
//
//                if (!StmtList()) {
//                    return false;
//                }
//                go_back();
//                return true;
//            }
//        }
//    }
//
//    if (temp[pointer] == "kwdefault") {
//        add_token_next();
//        if (temp[pointer] == "colon") {
//            add_token_next();
//
//            numbers.push_back("0");
//            new_pointer();
//
//            string_generator("kwdefault colon StmtList");
//
//            if (!StmtList()) {
//                return false;
//            }
//
//            go_back();
//            return true;
//        }
//    }
//    return false;
//}
//
//bool CasesList(){
//
//    int temp_point = number_pointer;
//
//    numbers.push_back("1");
//    new_pointer();
//
//    string_generator("ACase");
//
//    if (ACase()){
//
//        numbers.push_back("0");
//        new_pointer();
//
//        string_generator("CasesList");
//
//        if (!CasesList()){
//            return false;
//        }
//
//        go_back();
//
//        return true;
//    } else{
//        numbers.pop_back();
//        answer.pop_back();
//
//        for (int i = 0; i < number_pointer - temp_point + 1; i++){
//            go_back();
//        }
//
//        return true;
//    }
//}
//
//bool Cases(){
//
//    numbers.push_back("1");
//    new_pointer();
//
//    string_generator("ACase");
//
//    if (!ACase()){
//        return false;
//    }
//
//    numbers.push_back("0");
//    new_pointer();
//
//    string_generator("CasesList");
//
//    if (!CasesList()) {
//        return false;
//    }
//    go_back();
//    return true;
//}
//
//bool SwitchOp(){
//    if (temp[pointer] == "kwswitch"){
//        add_token_next();
//        if (temp[pointer] == "lpar"){
//            add_token_next();
//
//            numbers.push_back("1");
//            new_pointer();
//
//            string_generator("kwswitch lpar");
//
//            if (!E()){
//                return false;
//            }
//            go_back();
//
//            if (temp[pointer] == "rpar"){
//                add_token_next();
//                if (temp[pointer] == "lbrace"){
//                    add_token_next();
//
//                    numbers.push_back("1");
//                    new_pointer();
//
//                    string_generator("rpar lbrace Cases");
//
//                    if (!Cases()){
//                        return false;
//                    }
//
//                    if (temp[pointer] == "rbrace"){
//                        add_token_next();
//
//                        numbers.push_back("0");
//                        new_pointer();
//
//                        string_generator("rbrace");
//
//                        go_back();
//
//                        go_back();
//
//                        return true;
//                    }
//                }
//            }
//        }
//    }
//    return false;
//}
//
//bool ElsePart(){
//
//    if (temp[pointer] == "kwelse"){
//
//        add_token_next();
//
//        numbers.push_back("0");
//        new_pointer();
//
//        string_generator("kwelse Stmt");
//
//        if (!Stmt()){
//            return false;
//        }
//
//    }
//
//    go_back();
//
//    return true;
//}
//
//bool IfOp(){
//
//    numbers.push_back("0");
//    new_pointer();
//
//    string_generator("IfOp");
//
//    if (temp[pointer] == "kwif"){
//
//        add_token_next();
//
//        if (temp[pointer] == "lpar"){
//
//            numbers.push_back("1");
//            new_pointer();
//
//            string_generator("kwif lpar E");
//
//            add_token_next();
//
//            if (!E()){
//                return false;
//            }
//
//            go_back();
//
//
//            if (temp[pointer] == "rpar"){
//
//                add_token_next();
//
//
//                numbers.push_back("1");
//                new_pointer();
//
//                string_generator("rpar Stmt");
//
//                if (!Stmt()){
//                    return false;
//                }
//                numbers.push_back("0");
//                new_pointer();
//
//                string_generator("ElsePart");
//
//                if (!ElsePart()){
//                    return false;
//                }
//
//                go_back();
//
//                go_back();
//
//                return true;
//            }
//        }
//    }
//    numbers.pop_back();
//
//    answer.pop_back();
//
//    return false;
//}
//
//bool OOp(){
//    if (temp[pointer] == "kwout"){
//
//        numbers.push_back("0");
//        new_pointer();
//
//        string_generator("OOp");
//
//        add_token_next();
//
//        numbers.push_back("1");
//        new_pointer();
//
//        string_generator("kwout E");
//
//        if (!E()){
//            return false;
//        }
//
//        go_back();
//
//        if (temp[pointer] != "semicolon"){
//            return false;
//        }
//
//        add_token_next();
//
//        numbers.push_back("0");
//        new_pointer();
//
//        string_generator("semicolon");
//
//        go_back();
//
//        go_back();
//
//        go_back();
//
//        return true;
//    }
//    return false;
//}
//
//bool IOp(){
//    if (temp[pointer] == "kwin"){
//
//        numbers.push_back("0");
//        new_pointer();
//
//        string_generator("IOp");
//
//
//        add_token_next();
//
//
//        if (temp[pointer] == "id"){
//
//            std::string temp_id = temp_lexem;
//
//            add_token_next();
//
//            if (temp[pointer] != "semicolon"){
//                return false;
//            }
//
//            numbers.push_back("0");
//            new_pointer();
//
//            string_generator("kwin " + temp_id + " semicolon");
//
//            go_back();
//
//            add_token_next();
//
//            go_back();
//
//            go_back();
//            return true;
//        }
//    }
//    return false;
//}
//
//bool ForLoop(){
//    if (temp[pointer] == "opinc"){
//
//        add_token_next();
//
//        if (temp[pointer] == "id"){
//
//            numbers.push_back("0");
//            new_pointer();
//
//            string_generator("opinc " + temp_lexem);
//
//            add_token_next();
//
//            go_back();
//
//            go_back();
//
//            return true;
//        }
//        return false;
//    }
//
//    numbers.push_back("1");
//    new_pointer();
//
//    string_generator("AssignOrCall");
//
//    int temp_point = pointer;
//    if (AssignOrCall()){
//        go_back();
//        return true;
//    }
//    else {
//        numbers.pop_back();
//        answer.pop_back();
//        pointer = temp_point;
//        go_back();
//        return true;
//    }
//}
//
//bool ForExp(){
//    int temp_point = pointer;
//
//    numbers.push_back("0");
//    new_pointer();
//
//    string_generator("E");
//
//    int aboba = answer.size() - 1;
//    int aboba_number = numbers.size() - 1;
//
//    if (E()){
//
//        go_back();
//
//        go_back();
//
//        return true;
//
//    } else {
//
//        answer.erase(answer.begin() + aboba, answer.end());
//        numbers.erase(numbers.begin() + aboba_number, numbers.end());
//
//        numbers.pop_back();
//
//        pointer = temp_point;
//
//        return true;
//    }
//}
//
//bool ForInit(){
//    int temp_point = pointer;
//
//    numbers.push_back("1");
//    new_pointer();
//
//    string_generator("Type");
//
//    if (!Type()){
//        numbers.pop_back();
//        answer.pop_back();
//        pointer = temp_point;
//    }
//
//    numbers.push_back("0");
//    new_pointer();
//
//    string_generator("AssignOrCall");
//
//    if (AssignOrCall()){
//        go_back();
//        return true;
//    } else {
//        numbers.pop_back();
//        answer.pop_back();
//        go_back();
//        pointer = temp_point;
//        return true;
//    }
//}
//
//bool ForOp(){
//
//    numbers.push_back("0");
//    new_pointer();
//
//    string_generator("ForOp");
//
//    if (temp[pointer] == "kwfor"){
//        add_token_next();
//        if (temp[pointer] == "lpar"){
//            add_token_next();
//
//            numbers.push_back("1");
//            new_pointer();
//
//            string_generator("kwfor lpar ForInit");
//
//            if (!ForInit()){
//                return false;
//            }
//
//            if (temp[pointer] == "semicolon"){
//                add_token_next();
//
//                numbers.push_back("1");
//                new_pointer();
//
//                string_generator("semicolon ForExp");
//
//                if (!ForExp()){
//                    return false;
//                }
//
//                if (temp[pointer] == "semicolon"){
//                    add_token_next();
//
//                    numbers.push_back("1");
//                    new_pointer();
//
//                    string_generator("semicolon ForLoop");
//
//                    if (!ForLoop()){
//                        return false;
//                    }
//
//                    if (temp[pointer] == "rpar"){
//                        numbers.push_back("0");
//                        new_pointer();
//
//                        string_generator("rpar Stmt");
//
//                        add_token_next();
//
//                        if (!Stmt()){
//                            return false;
//                        }
//
//                        go_back();
//
//                        go_back();
//
//                        return true;
//                    }
//
//                }
//            }
//        }
//    }
//    numbers.pop_back();
//    answer.pop_back();
//    return false;
//}
//
//bool WhileOp(){
//
//    numbers.push_back("0");
//    new_pointer();
//
//    string_generator("WhileOp");
//
//    if (temp[pointer] == "kwwhile"){
//
//        add_token_next();
//
//        if (temp[pointer] == "lpar"){
//
//            numbers.push_back("1");
//            new_pointer();
//
//            string_generator("kwwhile lpar E");
//
//            add_token_next();
//            if (!E()){
//                return false;
//            }
//
//            go_back();
//
//            numbers.push_back("0");
//            new_pointer();
//
//            string_generator("rpar");
//
//            if (temp[pointer] == "rpar"){
//
//                add_token_next();
//
//                go_back();
//
//                go_back();
//
//                go_back();
//
//                return true;
//            }
//        }
//    }
//    answer.pop_back();
//
//    numbers.pop_back();
//
//    return false;
//}
//
//bool AssignOrCallList(){
//    if (temp[pointer] == "opassign"){
//
//        numbers.push_back("0");
//        new_pointer();
//
//        string_generator("opassign E");
//
//        add_token_next();
//
//        if (!E()){
//            return false;
//        }
//        go_back();
//
//        go_back();
//        return true;
//    }
//    else if (temp[pointer] == "lpar"){
//
//        numbers.push_back("1");
//        new_pointer();
//
//        string_generator("lpar ParamList");
//
//        add_token_next();
//
//        if (!ParamList()){
//            return false;
//        }
//
//        if (temp[pointer] == "rpar"){
//            numbers.push_back("0");
//            new_pointer();
//
//            string_generator("rpar");
//            add_token_next();
//
//
//            go_back();
//
//            go_back();
//
//            return true;
//        }
//    }
//    else{
//        return false;
//    }
//}
//
//bool AssignOrCall(){
//    if (temp[pointer] == "id"){
//        numbers.push_back("0");
//        new_pointer();
//
//        string_generator(temp_lexem + " AssignOrCallList");
//        add_token_next();
//        if (!AssignOrCallList()){
//            return false;
//        }
//        go_back();
//        return true;
//    }
//    return false;
//}
//
//bool AssignOrCallOp(){
//    numbers.push_back("0");
//    new_pointer();
//
//    string_generator("AssignOrCallOp");
//
//    numbers.push_back("1");
//    new_pointer();
//
//    string_generator("AssignOrCall");
//
//    if (!AssignOrCall()){
//        numbers.pop_back();
//        numbers.pop_back();
//        answer.pop_back();
//        answer.pop_back();
//        return false;
//    }
//
//
//    if (temp[pointer] != "semicolon"){
//        return false;
//    }
//    numbers.push_back("0");
//    new_pointer();
//
//    string_generator("semicolon");
//
//    add_token_next();
//
//    go_back();
//
//    go_back();
//
//    go_back();
//
//    return true;
//}
//
bd ParamListList(){
    if (temp[pointer] == "end"){
        return {false, ""};
    }

    if (temp[pointer] == "comma"){

        numbers.push_back("1");
        new_pointer();

        string_generator("comma Type");

        add_token_next();

        bd Type_answer = Type();

        if (!Type_answer.first){
            return {false, ""};
        }
        if (temp[pointer] == "id"){
            std::string name = addVar(temp_lexem, contexts[contexts.size() - 1], Type_answer.second, "0");

            if (name == "error"){
                return {false, ""};
            }

            numbers.push_back("0");
            new_pointer();

            string_generator(temp_lexem + " ParamListList");

            add_token_next();

            bd ParamListList_answer = ParamListList();

            if (!ParamListList_answer.first){
                return {false, ""};
            }

            go_back();

            return {true, std::to_string(std::stoi(ParamListList_answer.second) + 1)};
        }
    }
    go_back();

    return {true, "0"};
}

bd ParamList() {
    if (temp[pointer] == "end") {
        return {false, ""};
    }

    int temp_point = pointer;

    numbers.push_back("1");
    new_pointer();

    string_generator("Type");

    bd Type_answer = Type();

    if (Type_answer.first) {
        if (temp[pointer] == "id") {

            std::string name = addVar(temp_lexem, contexts[contexts.size() - 1], Type_answer.second, "0");

            if (name == "error"){
                return {false, ""};
            }

            numbers.push_back("0");
            new_pointer();

            string_generator(temp_lexem + " ParamListList");

            add_token_next();

            bd ParamListList_answer = ParamListList();

            if (!ParamListList_answer.first) {
                return {false, ""};
            }

            go_back();

            return {true, std::to_string(std::stoi(ParamListList_answer.second) + 1)};

        } else {
            return {false, ""};
        }
    } else {
        answer.pop_back();
        numbers.pop_back();
        pointer = temp_point;
    }

    go_back();
    return {true, "0"};
}

bool InitVar(std::string p, std::string q){
    if (temp[pointer] == "end"){
        return false;
    }

    if (temp[pointer] == "opassign"){
        add_token_next();
        if (temp[pointer] == "num") {

            std::string new_variable = addVar(q, contexts[contexts.size() - 1], p, temp_lexem);

            if (new_variable == "error"){
                return false;
            }

            numbers.push_back("0");
            new_pointer();

            string_generator("opassign " + temp_lexem);

            generate_atom(contexts[contexts.size() - 1], "MOV", "'" + temp_lexem + "'", "", new_variable);

            add_token_next();

            go_back();

            go_back();

            return true;
        }
        else if (temp[pointer] == "char"){
            std::string new_variable = addVar(q, contexts[contexts.size() - 1], p, "'" + temp_lexem + "'");

            if (new_variable == "error"){
                return false;
            }

            numbers.push_back("0");
            new_pointer();

            string_generator(temp_lexem);

            generate_atom(contexts[contexts.size() - 1], "MOV", "'" + temp_lexem + "'", "", new_variable);

            add_token_next();

            go_back();

            go_back();

            return true;
        }
        return false;
    }
    std::string new_variable = addVar(q, contexts[contexts.size() - 1], p, "0");

    if (new_variable == "error"){
        return false;
    }

    go_back();
    return true;
}

bool DeclVarList(std::string p){

    if (temp[pointer] == "end"){
        return false;
    }

    if (temp[pointer] == "comma"){

        add_token_next();

        if (temp[pointer] == "id"){

            numbers.push_back("1");
            new_pointer();

            std::string temp_id = temp_lexem;

            string_generator("comma " + temp_lexem + " InitVar");

            add_token_next();

            if (!InitVar(p, temp_id)){
                return false;
            }

            numbers.push_back("0");
            new_pointer();

            string_generator("DeclVarList");

            if (!DeclVarList(p)){
                return false;
            }
        }
    }

    go_back();
    return true;
}

bool DeclareStmtList(std::string p, std::string q) {
    if (temp[pointer] == "end") {
        return false;
    }

    if (temp[pointer] == "lpar") {
        if (contexts[contexts.size() - 1] != "-1") {
            return false;
        }

        std::string CList = addFunc(q, p, "0");
        contexts.push_back(CList);

        add_token_next();

        numbers.push_back("1");
        new_pointer();

        string_generator("lpar ParamList");

        bd ParamList_answer = ParamList();

        if (!ParamList_answer.first) {
            return false;
        }

        for (auto &i: AtomsMap["-1"]) {
            if (std::to_string(i.number_of_id) == CList) {
                i.len = ParamList_answer.second;
            }
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

                    generate_atom(contexts[contexts.size() - 1], "RET", "", "", "'0'");

                    contexts.pop_back();

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

        if (temp[pointer] == "num") {
            std::string new_variable = addVar(q, contexts[contexts.size() - 1], p, temp_lexem);

            if (new_variable == "error"){
                return false;
            }

            numbers.push_back("1");
            new_pointer();

            string_generator("opassign " + temp_lexem + " DeclVarList");

            generate_atom(contexts[contexts.size() - 1], "MOV", "'" + temp_lexem + "'", "", new_variable);

            add_token_next();

            bool DeclVarList_answer = DeclVarList(p);

            if (!DeclVarList_answer) {
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
            } else{
                return false;
            }
        } else if (temp[pointer] == "char") {
            std::string new_variable = addVar(q, contexts[contexts.size() - 1], p, "'" + temp_lexem + "'");

            if (new_variable == "error"){
                return false;
            }

            numbers.push_back("1");
            new_pointer();

            string_generator("opassign " + temp_lexem + " DeclVarList");

            generate_atom(contexts[contexts.size() - 1], "MOV", "'" + temp_lexem + "'", "", new_variable);

            add_token_next();

            bool DeclVarList_answer = DeclVarList(p);

            if (!DeclVarList_answer) {
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
            } else {
                return false;
            }
        }
    }
    else {
        std::string new_variable = addVar(q, contexts[contexts.size() - 1], p, "0");

        if (new_variable == "error"){
            return false;
        }

        numbers.push_back("1");
        new_pointer();

        string_generator("DeclVarList");

        if (!DeclVarList(p)) {
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
        } else {
            return false;
        }
    }
    return false;
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

    bd Type_answer = Type();

    if (!Type_answer.first){
        numbers.pop_back();
        numbers.pop_back();
        answer.pop_back();
        answer.pop_back();
        return false;
    }

    if (temp[pointer] != "id"){
        return false;
    }
    std::string name = temp_lexem;

    numbers.push_back("0");
    new_pointer();

    string_generator(temp_lexem + " DeclareStmtList");

    add_token_next();

    if (!DeclareStmtList(Type_answer.second, name)){
        return false;
    }

    go_back();
    return true;
}

bd Type(){
    if (temp[pointer] == "end"){
        return {false, ""};
    }

    if (temp[pointer] == "kwint"){
        add_token_next();

        numbers.push_back("0");
        new_pointer();

        string_generator("kwint");

        go_back();

        go_back();

        return {true, "kwint"};
    }
    if (temp[pointer] == "kwchar"){
        add_token_next();

        numbers.push_back("0");
        new_pointer();

        string_generator("kwchar");

        go_back();

        go_back();

        return {true, "kwchar"};
    }
    return {false, ""};
}

bool Stmt() {
    if (temp[pointer] == "end"){
        return false;
    }

    int temp_point = pointer;

    int temp_number = number_pointer;

    if (DeclareStmt()){
        go_back();
        return true;
    } else {
        number_pointer = temp_number;
        pointer = temp_point;}
//    if (AssignOrCallOp()){
//        return true;
//    } else {
//        number_pointer = temp_number;
//        pointer = temp_point;}
//    if (WhileOp()){
//        return true;
//    } else {
//        number_pointer = temp_number;
//        pointer = temp_point;}
//    if (ForOp()){
//        return true;
//    } else {pointer = temp_point;}
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
//
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

        bd E_answer = E();

        if (!E_answer.first){
            return false;
        }
        go_back();

        generate_atom(contexts[contexts.size() - 1], "RET", "", "", E_answer.second);

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

bd ArgListList(std::string id = ""){
    if (temp[pointer] == "comma"){
        numbers.push_back("1");
        new_pointer();

        string_generator("comma E");

        add_token_next();

        bd E_result = E();
        if (!E_result.first) {
            return {false, ""};
        }
        go_back();

        numbers.push_back("0");
        new_pointer();

        string_generator("ArgListList");

        bd ArgListList_result = ArgListList();
        if (!ArgListList_result.first) {
            return {false, ""};
        }

        generate_atom(contexts[0], "PARAM", "", "", E_result.second);

        go_back();
        std::string number = std::to_string(std::stoi(ArgListList_result.second) + 1);
        return {true, number};
    }
    go_back();
    return {true, "0"};
}

bd ArgList() {
    if (temp[pointer] == "id") {

        numbers.push_back("1");
        new_pointer();
        string_generator("id E");

        bd E_result = E();
        if (!E_result.first) {
            return {false, ""};
        }
        go_back();

        numbers.push_back("0");
        new_pointer();
        string_generator("ArgListList");

        bd ArgListList_result = ArgListList();
        if (!ArgListList_result.first) {
            return {false, ""};
        }

        generate_atom(contexts[0], "PARAM", "", "", E_result.second);

        std::string number = std::to_string(std::stoi(ArgListList_result.second) + 1);

        go_back();

        return {true, number};
    }
    go_back();
    return {true, "0"};
}

bd E1_shtrih(std::string id) {
    int point = number_pointer;
    if (temp[pointer] == "opinc"){
        add_token_next();

        auto s = checkVar(id);
        auto r = alloc(contexts[contexts.size() - 1]);

        generate_atom(contexts[contexts.size() - 1], "MOV", s, "", r);
        generate_atom(contexts[contexts.size() - 1], "ADD", s, "'1'", s);

        numbers.push_back("0");
        new_pointer();

        string_generator("opinc");

        go_back();
        go_back();
        return {true, r};
    }
    else if (temp[pointer] == "lpar"){
        add_token_next();

        numbers.push_back("1");
        new_pointer();

        string_generator("lpar ArgList");

        bd ArgList_answer = ArgList();

        if (!ArgList_answer.first){
            return {false, ""};
        }

        point = number_pointer;

        if (temp[pointer] == "rpar"){
            add_token_next();

            auto s = checkFunc(id, ArgList_answer.second);
            auto r = alloc(contexts[contexts.size() - 1]);

            generate_atom(contexts[contexts.size() - 1], "CALL", s, "", r);

            numbers.push_back("0");
            new_pointer();

            string_generator("rpar");

            go_back();
            go_back();
            return {true, r};

        } else {
            return {false, ""};
        }
    }
    auto q = checkVar(id);

    go_back();
    return {true, q};
}

bd E1() {
    int point = number_pointer;
    if (temp[pointer] == "opinc") {
        add_token_next();

        numbers.push_back("0");
        new_pointer();

        string_generator("opinc");

        if (temp[pointer] == "id") {

            auto q = checkVar(temp_lexem);
            generate_atom(contexts[contexts.size() - 1], "ADD", q, "1", q);

            numbers.push_back("0");
            new_pointer();

            string_generator(temp_lexem);

            add_token_next();

            go_back();
            go_back();
            go_back();
            return {true, q};
        }
        return {false, ""};
    }
    else if (temp[pointer] == "num") {
        auto value = temp_lexem;

        numbers.push_back("0");
        new_pointer();

        string_generator(temp_lexem);

        add_token_next();

        go_back();
        go_back();
        return {true, "'" + value + "'"};
    }
    else if (temp[pointer] == "id") {
        auto temp_id = temp_lexem;

        numbers.push_back("0");
        new_pointer();

        string_generator(temp_id + " E1List");

        add_token_next();

        bd E1_shtrih_answer = E1_shtrih(temp_id);

        if (!E1_shtrih_answer.first){
            return {false, ""};
        }
        go_back();
        return {true, E1_shtrih_answer.second};
    }
    else if (temp[pointer] == "lpar") {
        add_token_next();

        numbers.push_back("1");
        new_pointer();

        string_generator("lpar E");

        bd E_answer = E();

        if (!E_answer.first) {
            return {false, ""};
        }
        go_back();

        if (temp[pointer] == "rpar") {
            add_token_next();

            numbers.push_back("0");
            new_pointer();

            string_generator("rpar");

            go_back();
            go_back();
            return {true, E_answer.second};
        }
    }
    return {false, ""};
}

bd E2() {
    int point = number_pointer;
    if (temp[pointer] == "opnot") {
        add_token_next();

        numbers.push_back("0");
        new_pointer();

        string_generator("opnot E1");

        auto E1_answer = E1();

        if (!E1_answer.first){
            return {false, ""};
        }

        auto r = alloc(contexts[contexts.size() - 1]);
        generate_atom(contexts[contexts.size() - 1], "NOT", E1_answer.second, r);

        go_back();
        return {true, r};

    } else {
        numbers.push_back("0");
        new_pointer();

        string_generator("E1");

        bd E1_answer = E1();

        if (!E1_answer.first) {
            return {false, ""};
        }
        go_back();
        return {true, E1_answer.second};
    }
}

bd E3_shtrih(std::string id) {
    if (temp[pointer] == "opmul") {
        add_token_next();

        int point = number_pointer;

        numbers.push_back("1");
        new_pointer();

        string_generator("opmul E2");

        bd E2_answer = E2();

        if (!E2_answer.first) {
            return {false, ""};
        }

        auto s = alloc(contexts[contexts.size() - 1]);
        generate_atom(contexts[contexts.size() - 1], "MUL", id, E2_answer.second, s);

        point = number_pointer;

        numbers.push_back("0");
        new_pointer();

        string_generator("E3List");

        bd E3_shtrih_answer = E3_shtrih(s);

        if (!E3_shtrih_answer.first) {
            return {false, ""};
        }
        go_back();
        return {true, E3_shtrih_answer.second};
    }
    go_back();
    return {true, id};
}

bd E3() {
    int point = number_pointer;

    numbers.push_back("1");
    new_pointer();

    string_generator("E2");

    bd E2_answer = E2();

    if (!E2_answer.first) {
        return {false, ""};
    }

    point = number_pointer;

    numbers.push_back("0");
    new_pointer();

    string_generator("E3List");

    bd E3_shtrih_answer = E3_shtrih(E2_answer.second);

    if (!E3_shtrih_answer.first){
        return {false, ""};
    }
    go_back();
    return {true, E3_shtrih_answer.second};
}

bd E4_shtrih(std::string id) {
    if (temp[pointer] == "opplus") {
        add_token_next();

        int point = number_pointer;

        numbers.push_back("1");
        new_pointer();

        string_generator("opplus E3");

        bd E3_answer = E3();

        if (!E3_answer.first) {
            return {false, ""};
        }
        auto s = alloc(contexts[contexts.size() - 1]);
        generate_atom(contexts[contexts.size() - 1], "ADD", id, E3_answer.second, s);

        point = number_pointer;

        numbers.push_back("0");
        new_pointer();

        string_generator("E4List");

        bd E4_shtrih_answer = E4_shtrih(s);

        if (!E4_shtrih_answer.first) {
            return {false, ""};
        }
        go_back();
        return {true, E4_shtrih_answer.second};
    }
    else if (temp[pointer] == "opminus") {
        add_token_next();

        int point = number_pointer;

        numbers.push_back("1");
        new_pointer();

        string_generator("opminus E3");

        bd E3_answer = E3();

        if (!E3_answer.first) {
            return {false, ""};
        }
        auto s = alloc(contexts[contexts.size() - 1]);
        generate_atom(contexts[contexts.size() - 1], "SUB", id, E3_answer.second, s);

        point = number_pointer;

        numbers.push_back("0");
        new_pointer();

        string_generator("E4List");

        auto E4_shtrih_answer = E4_shtrih(s);

        if (!E4_shtrih_answer.first) {
            return {false, ""};
        }
        go_back();
        return {true, E4_shtrih_answer.second};
    }
    go_back();
    return {true, id};
}

bd E4() {
    int point = number_pointer;

    numbers.push_back("1");
    new_pointer();

    string_generator("E3");

    bd E3_answer = E3();

    if (!E3_answer.first) {
        return {false, ""};
    }

    point = number_pointer;

    numbers.push_back("0");
    new_pointer();

    string_generator("E4List");

    bd E4_shtrih_answer = E4_shtrih(E3_answer.second);

    if (!E4_shtrih_answer.first){
        return {false, ""};
    }
    go_back();
    return {true, E4_shtrih_answer.second};
}

bd E5_shtrih(std::string id) {
    if (temp[pointer] == "opeq") {
        add_token_next();

        int point = number_pointer;

        numbers.push_back("0");
        new_pointer();

        string_generator("opeq E4");

        bd E4_answer = E4();

        if (!E4_answer.first) {
            return {false, ""};
        }
        auto s = alloc(contexts[contexts.size() - 1]);
        auto l = newLabel();

        generate_atom(contexts[contexts.size() - 1], "MOV", "1", "", s);
        generate_atom(contexts[contexts.size() - 1], "EQ", id, E4_answer.second, "L" + l);
        generate_atom(contexts[contexts.size() - 1], "MOV", "0", "", s);
        generate_atom(contexts[contexts.size() - 1], "LBL", "", "", "L" + l);

        go_back();
        return {true, s};

    }
    else if (temp[pointer] == "opne") {
        add_token_next();

        int point = number_pointer;

        numbers.push_back("0");
        new_pointer();

        string_generator("opne E4");

        bd E4_answer = E4();

        if (!E4_answer.first) {
            return {false, ""};
        }
        auto s = alloc(contexts[contexts.size() - 1]);
        auto l = newLabel();

        generate_atom(contexts[contexts.size() - 1], "MOV", "1", "", s);
        generate_atom(contexts[contexts.size() - 1], "NE", id, E4_answer.second, "L" + l);
        generate_atom(contexts[contexts.size() - 1], "MOV", "0", "", s);
        generate_atom(contexts[contexts.size() - 1], "LBL", "", "", "L" + l);

        go_back();
        return {true, s};
    }
    else if (temp[pointer] == "oplt") {
        add_token_next();

        int point = number_pointer;

        numbers.push_back("0");
        new_pointer();

        string_generator("oplt E4");

        bd E4_answer = E4();

        if (!E4_answer.first) {
            return {false, ""};
        }
        auto s = alloc(contexts[contexts.size() - 1]);
        auto l = newLabel();

        generate_atom(contexts[contexts.size() - 1], "MOV", "1", "", s);
        generate_atom(contexts[contexts.size() - 1], "LT", id, E4_answer.second, "L" + l);
        generate_atom(contexts[contexts.size() - 1], "MOV", "0", "", s);
        generate_atom(contexts[contexts.size() - 1], "LBL", "", "", "L" + l);

        go_back();
        return {true, s};
    }
    go_back();
    return {true, id};
}

bd E5() {
    int point = number_pointer;

    numbers.push_back("1");
    new_pointer();

    string_generator("E4");

    bd E4_answer = E4();

    if (!E4_answer.first) {
        return {false,""};
    }

    point = number_pointer;

    numbers.push_back("0");
    new_pointer();

    string_generator("E5List");

    bd E5_shtrih_answer = E5_shtrih(E4_answer.second);

    if (!E5_shtrih_answer.first) {
        return {false, ""};
    }
    go_back();
    return {true, E5_shtrih_answer.second};
}


bd E6_shtrih(std::string id) {
    if (temp[pointer] == "opand") {
        add_token_next();

        int point = number_pointer;

        numbers.push_back("1");
        new_pointer();

        string_generator("opand E5");

        bd E5_answer = E5();

        if (!E5_answer.first) {
            return {false, ""};
        }

        auto s = alloc(contexts[contexts.size() - 1]);
        generate_atom(contexts[contexts.size() - 1], "AND", id, E5_answer.second, s);

        point = number_pointer;

        numbers.push_back("0");
        new_pointer();

        string_generator("E6List");

        bd E6_shtrih_answer = E6_shtrih(s);

        if (!E6_shtrih_answer.first) {
            return {false, ""};
        }
        go_back();
        return {true, E6_shtrih_answer.second};
    }
    go_back();
    return {true, id};
}

bd E6() {
    int point = number_pointer;

    numbers.push_back("1");
    new_pointer();

    string_generator("E5");

    bd E5_answer = E5();

    if (!E5_answer.first) {
        return {false, ""};
    }

    point = number_pointer;

    numbers.push_back("0");
    new_pointer();

    string_generator("E6List");

    bd E6_shtrih_answer = E6_shtrih(E5_answer.second);

    if (!E6_shtrih_answer.first) {
        return {false, ""};
    }
    go_back();
    return {true, E6_shtrih_answer.second};
}

bd E7_shtrih(std::string id) {
    if (temp[pointer] == "opor") {

        add_token_next();

        int point = number_pointer;

        numbers.push_back("1");
        new_pointer();

        string_generator("opor E6");

        bd E6_answer = E6();

        if (!E6_answer.first) {
            return {false, ""};
        }

        auto s = alloc(contexts[contexts.size() - 1]);
        generate_atom(contexts[contexts.size() - 1], "OR", id, E6_answer.second, s);

        point = number_pointer;

        numbers.push_back("0");
        new_pointer();

        string_generator("E7List");

        bd E7List_answer = E7_shtrih(s);

        if (!E7List_answer.first) {
            return {false, ""};
        }
        go_back();
        return {true, E7List_answer.second};
    }
    go_back();
    return {true, id};
}

bd E7() {
    int point = number_pointer;

    numbers.push_back("1");
    new_pointer();

    string_generator("E6");

    bd E6_answer = E6();

    if (!E6_answer.first){
        return {false, ""};
    }

    point = number_pointer;

    numbers.push_back("0");
    new_pointer();

    string_generator("E7List");

    bd E7List_answer = E7_shtrih(E6_answer.second);

    if (!E7List_answer.first) {
        return {false, ""};
    }
    go_back();
    return {true, E7List_answer.second};
}

bd E() {
    int point = number_pointer;
    numbers.push_back("0");
    new_pointer();

    string_generator("E7");

    bd E7_answer = E7();

    if (!E7_answer.first) {
        return {false, ""};
    }

    return {true, E7_answer.second};
}

int main() {
    Lexem lexem;
    lexem = lexer.nextLexem();
    std::string a = lexem.first;
    temp_lexem = lexem.second;
    temp.push_back(a);
    int adasd;
    bool A = StmtList();
    print_tree();
    print_atoms();
    streamline.close();
    if (A and temp[pointer] == "end" and Atoms.front().name != "error"){
        std::cout << "Correct expression";
    } else {
        std::cout << "Incorrect expression";
    }
    return 0;
}