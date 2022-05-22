#include "maketree.hh"

#include "../global/log.hh"

#include "lex.hh"

namespace ran
{

    syntax_tree make_tree(std::string code)
    {
        ran::log(RANC, "Making syntax tree...");
        std::vector<pair> lexlist = lexy(code); //生成词法表
        syntax_tree sttree =  produce_sttree(lexlist);
        return sttree;
    }

};
