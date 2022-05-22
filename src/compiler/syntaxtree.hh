#ifndef SYNTAXTREE_HH
#define SYNTAXTREE_HH

#include "compilerdef.hh"
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
        enum syntax
        {
            __module,
            
        };

    private:
        std::string word;
        __StTree *father;
        std::vector<__StTree *> child;
        syntax treetype;

    public:
        __StTree(std::string);
        ~__StTree(); //析构子树

        void addChild(__StTree *);
        void delLastChild();

        void setFather(__StTree *);
        __StTree *getFather();
    };

    class StTree
    {
    private:
        __StTree *root;
        __StTree *current;

    public:
        StTree(std::string);
        ~StTree();
    };
};

#endif
