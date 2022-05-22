#include "syntaxtree.hh"

namespace ran
{
    __StTree::__StTree(std::string word)
    {
        this->word = word;
    }

    __StTree::~__StTree()
    {
        for(__StTree *it : child)
        {
            delete it;
        }
    }

    void __StTree::addChild(__StTree *ch)
    {
        child.push_back(ch);
    }

    void __StTree::delLastChild()
    {
        child.pop_back();
    }

    void __StTree::setFather(__StTree *fa)
    {
        this->father = fa;
    }

    __StTree *__StTree::getFather()
    {
        return father;
    }

    StTree::StTree(std::string name)
    {
        root = new __StTree(name);
        current = root;
    }

    StTree::~StTree()
    {
        delete root;
    }
};
