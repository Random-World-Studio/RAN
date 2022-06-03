#include "syntaxtree.hh"

#include "../debug/sttree.hh"

#include "treeproducer.hh"

namespace ran
{
    std::string getmodname(std::vector<pair> &lexlist);
    void build_tree(syntax_tree, std::vector<pair>);

    syntax_tree produce_sttree(std::vector<pair> lexlist)
    {
        log(RANC, "Producing syntax tree...");
        std::string modname = getmodname(lexlist);
        syntax_tree prod = new StTree;
        {
            prod->father = nullptr;
            prod->type = syntax::__tag;
            prod->content = modname;
            prod->content_discription = "module";
        }
        //开始生成语法树
        build_tree(prod, lexlist);
        outputTree(prod, 0, true, true);
        log(RANC, "Exceeded producing syntax tree.");
        return prod;
    }

    std::string getmodname(std::vector<pair> &lexlist)
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

    void build_tree(syntax_tree sttree, std::vector<pair> lexlist)
    {
        while (lexlist.size() != 0)
        {
            if (lexlist.at(0).type == lextype::keyword) //处理关键字
            {
                if (lexlist.at(0).word == "export")
                {
                    export_flag = true;
                    LEXDEL;
                }
                else if (lexlist.at(0).word == "import")
                {
                    make_import(sttree, lexlist);
                }
                else if (lexlist.at(0).word == "struct")
                {
                    make_struct(sttree, lexlist);
                }
                else
                {
                    LEXDEL;
                }
            }
            else//不是关键字就是全局表达式
            {
                make_express(sttree, lexlist);
            }
        }
    }
};
