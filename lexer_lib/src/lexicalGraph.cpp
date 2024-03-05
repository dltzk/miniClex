#include "lexicalGraph.h"

using namespace std;

map<int, vector<Container>> LexemMachine = {
        {-1, {
                     {"", false, false, -1, "end"},
             }},
        {0, {
                     {" ", true, false, 0, ""},
                     {"\n", true, false, 0, ""},
                     {"(", false, false, 1, ""},
                     {")", false, false, 1, ""},
                     {"{", false, false, 1, ""},
                     {"}", false, false, 1, ""},
                     {";", false, false, 1, ""},
                     {",", false, false, 1, ""},
                     {".", false, false, 1, ""},
                     {">", false, false, 1, ""},
                     {"*", false, false, 1, ""},
                     {"<", true, false, 2, ""},
                     {"!", true, false, 4, ""},
                     {"=", true, false, 6, ""},
                     {"+", true, false, 8, ""},
                     {"|", true, false, 10, ""},
                     {"&", true, false, 12, ""},
                     {"'", true, false, 14, ""},
                     {"\"", true, false, 18, ""},
                     {"letter", false, false, 21, ""},
                     {"-", true, true, 22, ""},
                     {"\n", true, false, 0, ""},
                     {"digit", false, false, 23, ""},
                     {"eof", false, false, -1, "end"},
                     {"default", false, false, -1, "error"}
             }},
        {1, {
                     {"(", true, false, 0, "lpar"},
                     {")", true, false, 0, "rpar"},
                     {"{", true, false, 0, "lbrace"},
                     {"}", true, false, 0, "rbrace"},
                     {";", true, false, 0, "semicolon"},
                     {",", true, false, 0, "comma"},
                     {".", true, false, 0, "colon"},
                     {">", true, false, 0, "opgt"},
                     {"*", true, false, 0, "opmul"},
             }},
        {2, {
                     {"=", false, false, 3, ""},
                     {"default", false, false, 0, "oplt"}
             }},
        {3, {
                     {"default", true, false, 0, "ople"}
             }},
        {4, {
                     {"=", false, false, 5, ""},
                     {"default", false, false, 0, "opnot"}
             }},
        {5, {
                     {"default", true, false, 0, "opne"}
             }},
        {6, {
                     {"=", false, false, 7, ""},
                     {"default", false, false, 0, "opassign"}
             }},
        {7, {
                     {"default", true, false, 0, "opeq"}
             }},
        {8, {
                     {"+", false, false, 9, ""},
                     {"default", false, false, 0, "opplus"}
             }},
        {9, {
                     {"default", true, false, 0, "opinc"}
             }},
        {10, {
                     {"|", false, false, 11, ""},
                     {"default", false, false, -1, "error"}
             }},
        {11, {
                     {"default", true, false, 0, "opor"}
             }},
        {12, {
                     {"&", false, false, 13, ""},
                     {"default", false, false, -1, "error"}
             }},
        {13, {
                     {"default", true, false, 0, "opand"}
             }},
        {14, {
                     {"'", true, false, 15, ""},
                     {"default", true, true, 16, ""}
             }},
        {15, {
                     {"default", false, false, -1, "error"}
             }},
        {16, {
                     {"'", false, false, 17, ""},
                     {"default", false, false, -1, "error", true}
             }},
        {17, {
                     {"default", true, false, 0, "char"}
             }},
        {18, {
                     {"\"", false, false, 20, ""},
                     {"eof", false, false, 19, ""},
                     {"default", true, true, 18, ""}
             }},
        {19, {
                     {"default", false, false, -1, "error", true}
             }},
        {20, {
                     {"default", true, false, 0, "str"}
             }},
        {21, {
                     {"letter", true, true, 21, ""},
                     {"digit", true, true, 21, ""},
                     {"default", false, false, 0, "keyword or id"}
             }},
        {22, {
                     {"digit", true, true, 23, ""},
                     {"default", false, false, 0, "opminus", true}
             }},
        {23, {
                     {"digit", true, true, 23, ""},
                     {"default", false, false, 0, "num"}
             }}
};
