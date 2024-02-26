#ifndef MINICLEX_LEXICALGRAPH_H
#define MINICLEX_LEXICALGRAPH_H
#include <map>
#include <vector>
#include <string>

struct Container{
    std::string cache;
    bool read;
    bool save;
    int nextState;
    std::string lexem;
    bool need_to_clear = false;
};

extern std::map<int, std::vector<Container>> LexemMachine;

#endif //MINICLEX_LEXICALGRAPH_H
