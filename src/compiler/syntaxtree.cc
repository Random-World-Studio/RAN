#include "syntaxtree.hh"

namespace ran
{
    std::string getmodname(std::vector<pair> lexlist);

    syntax_tree produce_sttree(std::vector<pair> lexlist)
    {
        log(RANC, "Producing syntax tree...");
        std::string modname = getmodname(lexlist);
        syntax_tree prod = new StTree(modname);
        //开始生成语法树
        
        log(RANC, "Exceeded producing syntax tree.");
        return prod;
    }

    std::string getmodname(std::vector<pair> lexlist)
    {
        std::string modname;
        for (int i = 0; i < lexlist.size(); i++)
            if (lexlist.at(i).type == lextype::keyword && lexlist.at(i).word == "modname") //寻找模块名定义语句
                if (i + 1 < lexlist.size())
                {
                    if (lexlist.at(i + 1).type == lextype::tag)
                    {
                        modname = lexlist.at(i + 1).word;
                        //删除模块名定义语句
                        std::vector<pair>::iterator it = lexlist.begin();
                        for (int j = 0; j < i; j++)
                            it++;
                        lexlist.erase(it);
                        it = lexlist.begin();
                        for (int j = 0; j < i; j++)
                            it++;
                        lexlist.erase(it);
                        it = lexlist.begin();
                        for (int j = 0; j < i; j++)
                            it++;
                        if (it->type == lextype::__operator && it->word == ";")
                            lexlist.erase(it);
                        else
                        {
                            err(RANC, "';' excepted after modname definition.");
                            exit_compiling(-5);
                        }
                        break;
                    }
                    else
                    {
                        err(RANC, "Modname excepted after keyword 'modname'.");
                        exit_compiling(-3);
                    }
                }
                else
                {
                    err(RANC, "Modname definition not terminated until end of file.");
                    exit_compiling(-4);
                }
        log(RANC, std::string("") + "modname: " + modname);
        return modname;
    }

    __StTree::__StTree(std::string word)
    {
        this->word = word;
    }

    __StTree::~__StTree()
    {
        for (__StTree *it : child)
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

    void __StTree::setType(syntax t)
    {
        this->treetype = t;
    }

    __StTree::syntax __StTree::getType()
    {
        return this->treetype;
    }

    std::vector<__StTree *> __StTree::getChildList()
    {
        return child;
    }

    StTree::StTree(std::string name)
    {
        root = new __StTree(name);
        current = root;
        current->setType(__StTree::syntax::__module);
        current->setFather(nullptr);
    }

    StTree::~StTree()
    {
        delete root;
    }

    bool StTree::switch_to_child(int child)
    {
        if (current->getChildList().size() > child)
            current = current->getChildList().at(child);
        else
            return false;
        return true;
    }

    bool StTree::switch_to_father()
    {
        if (current->getFather())
            current = current->getFather();
        else
            return false;
        return true;
    }

};
