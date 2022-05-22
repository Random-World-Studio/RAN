#ifndef SYNTAXTREE_HH
#define SYNTAXTREE_HH

#include "compilerdef.hh"
#include "lex.hh"

#include "../global/log.hh"

#include <vector>

namespace ran
{
    /**
     * @brief 语法树节点
     * 用于构建出代码的逻辑结构
     */
    class __StTree
    {
    public:
        enum syntax
        {
            __module,
            __struct,
            __function,
            __variable,
            __operator,
            __expression,
            __rightval,
        };

    private:
        std::string word;
        __StTree *father;
        std::vector<__StTree *> child;
        syntax treetype;

    public:
        __StTree(std::string);
        ~__StTree();

        void addChild(__StTree *);
        void delLastChild();

        void setFather(__StTree *);
        __StTree *getFather();

        void setType(syntax t);
        syntax getType();

        std::vector<__StTree *> getChildList();
    };

    class StTree//语法树容器
    {
    private:
        __StTree *root;
        __StTree *current;

    public:
        StTree(std::string);
        ~StTree();

        bool switch_to_child(int child);
        bool switch_to_father();
    };

    typedef StTree *syntax_tree;//重定义语法树容器指针

    syntax_tree produce_sttree(std::vector<pair>);
};

#endif
