#ifndef SYNTAXTREE_HH
#define SYNTAXTREE_HH

#include "compilerdef.hh"
#include "lex.hh"

#include <vector>
#include <set>

namespace ran
{
    enum syntax
    {
        __block,
        __expression,
        __number,
        __tag,
    };

    struct StTree //语法树容器
    {
        StTree *father;
        std::vector<StTree *> child;

        std::string content;             //内容
        std::string content_discription; //内容描述
        syntax type;                     //类型
    };

    typedef StTree *syntax_tree; //重定义语法树容器指针

    syntax_tree produce_sttree(std::vector<pair>);
};

#endif
