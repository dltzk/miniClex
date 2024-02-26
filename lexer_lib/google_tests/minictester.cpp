#include "gtest/gtest.h"
#include "../Lexer_lib/lexer.h"
#include <iomanip>

std::vector<Lexem> first_answer = {{"keyword", "kwint"},{"id", "main"},{"lpar", ""},{"keyword", "kwint"},{"id", "a"},{"comma", ""},{"keyword", "kwint"},{"id", "b"},{"rpar", ""},{"lbrace", ""},{"keyword", "kwint"},{"id", "c"},{"opassign", ""},{"num", "321321321"},{"semicolon", ""},{"keyword", "kwif"},{"lpar", ""},{"id", "a"},{"oplt", ""},{"id", "b"},{"rpar", ""},{"lbrace", ""},{"id", "a"},{"opassign", ""},{"id", "b"},{"semicolon", ""},{"rbrace", ""},{"keyword", "kwelse"},{"lbrace", ""},{"id", "c"},{"opassign",""},{"num", "2"},{"opmul", ""},{"id", "b"},{"semicolon", ""},{"id", "b"},{"opassign", ""},{"num", "3"},{"opmul", ""},{"id", "c"},{"semicolon", ""},{"rbrace", ""},{"keyword", "kwout"},{"lpar", ""},{"id", "a"},{"rpar", ""},{"semicolon", ""},{"id", "a"},{"opassign", ""},{"num", "5"},{"semicolon", ""},{"rbrace", ""},{"end", ""}};
std::vector<Lexem> second_answer = {{"keyword", "kwint"},{"id", "main"},{"lpar", ""},{"keyword", "kwint"},{"id", "a"},{"comma", ""},{"keyword", "kwint"},{"id", "b"},{"rpar", ""},{"lbrace", ""},{"keyword", "kwint"},{"id", "c"},{"opassign", ""},{"num", "321"},{"semicolon", ""},{"keyword", "kwif"},{"lpar", ""},{"id", "a"},{"opgt", ""},{"opassign", ""},{"id", "b"},{"rpar", ""},{"lbrace", ""},{"id", "c"},{"opassign", ""},{"num", "43"},{"semicolon", ""},{"rbrace", ""},{"keyword", "kwelse"},{"lbrace", ""},{"id", "c"},{"opassign", ""},{"num", "2"},{"opmul", ""},{"id", "a"},{"semicolon", ""},{"rbrace", ""},{"keyword", "kwout"},{"lpar",""},{"id", "a"},{"rpar", ""},{"semicolon", ""},{"keyword", "kwout"},{"lpar", ""},{"id", "b"},{"rpar", ""},{"semicolon",""},{"rbrace", ""},{"end", ""}};
std::vector<Lexem> third_answer = {{"keyword", "kwint"},{"id", "a"},{"semicolon", ""},{"id", "arrr"},{"lbrace", ""},{"rbrace", ""},{"opplus", ""},{"opminus", ""},{"end", ""}};

TEST(testSuit, Test1) {
    Lexem lexem;
    std::fstream streamline1(R"(C:\Users\Juzo Suzuya\CLionProjects\miniClex\firsttestfile.txt)");
    Lexer lexer(streamline1);
    int i = 0;
    while (true){
        lexem = lexer.nextLexem();
        EXPECT_EQ(lexem, first_answer[i]);
        if (lexem.first == "error" or lexem.first == "end") {
            break;
        }
        i++;
    }
};

TEST(testSuit, Test2) {
    Lexem lexem;
    std::fstream streamline1(R"(C:\Users\Juzo Suzuya\CLionProjects\miniClex\secondtestfile.txt)");
    Lexer lexer(streamline1);
    int i = 0;
    while (true){
        lexem = lexer.nextLexem();
        EXPECT_EQ(lexem, second_answer[i]);
        if (lexem.first == "error" or lexem.first == "end") {
            break;
        }
        i++;
    }
};

TEST(testSuit, Test3) {
    Lexem lexem;
    std::fstream streamline1(R"(C:\Users\Juzo Suzuya\CLionProjects\miniClex\thirdtestfile.txt)");
    Lexer lexer(streamline1);
    int i = 0;
    while (true){
        lexem = lexer.nextLexem();
        EXPECT_EQ(lexem, third_answer[i]);
        if (lexem.first == "error" or lexem.first == "end") {
            break;
        }
        i++;
    }
}


