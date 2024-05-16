//
// Created by Juzo Suzuya on 25.04.2024.
//

#ifndef MINICLEX_LL_H
#define MINICLEX_LL_H

struct Atom {
    std::string context;
    std::string name;
    std::string first;
    std::string second;
    std::string third;
};

struct Params {
    std::string name;
    std::string scope;
    std::string type;
    std::string init;
    std::string kind;
    std::string len;
    int number_of_id;
};

#endif //MINICLEX_LL_H
