#include "maketree.hh"

#include "../global/log.hh"

#include "lex.hh"
#include "syntaxtree.hh"

namespace ran
{

    void make_tree(std::string code)
    {
        ran::log(RANC, "Making gramma tree...");
        std::vector<pair> lexlist = lexy(code); //生成词法表
    }

};
