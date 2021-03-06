#define LEXDEL lexlist.erase(lexlist.begin())

#include "../global/puncutation.hh"

namespace ran
{

    bool export_flag = false;

    void make_import(syntax_tree sttree, std::vector<pair> &lexlist)
    {
        if (lexlist.at(1).type != lextype::tag) //如果紧跟struct的内容不是一个tag就报错
        {
            err(RANC, "Empty modname imported.");
            exit_compiling(-7);
        }
        syntax_tree node = new StTree;
        {
            node->father = sttree;
            node->type = syntax::__tag;
            node->content = lexlist.at(1).word;
            node->content_discription = lexlist.at(0).word;
            sttree->child.push_back(node);
        }
        LEXDEL;
        LEXDEL;
        if (lexlist.at(0).word != ";") //没有以;结尾就报错
        {
            err(RANC, "';' needed after importing.");
            exit_compiling(-8);
        }
        LEXDEL;
    }

    void make_struct(syntax_tree sttree, std::vector<pair> &lexlist)
    {
        if (lexlist.at(1).type != lextype::tag) //不允许匿名结构类型
        {
            err(RANC, "Unexpected unnamed structure.");
            exit_compiling(-9);
        }
        syntax_tree node = new StTree;
        {
            node->father = sttree;
            node->content = lexlist.at(1).word;
            node->type = syntax::__block;
            node->content_discription = lexlist.at(0).word;
            sttree->child.push_back(node);
        }
        LEXDEL;
        LEXDEL;
        if (lexlist.at(0).word != ":") //不允许未定义结构
        {
            err(RANC, "Struct definition nedded.");
            exit_compiling(-10);
        }
        LEXDEL;
        //开始
        sttree = node;
        int membercount = 0; //成员计数，用于标记匿名成员
        while (lexlist.at(0).word != "endstruct" && !lexlist.empty())
        {
            if (lexlist.at(0).type == lextype::keyword) //关键字开头的是匿名成员
            {
                syntax_tree node = new StTree;
                {
                    node->father = sttree;
                    node->type = syntax::__tag;
                    node->content = std::to_string(membercount);
                    node->content_discription = lexlist.at(0).word;
                    sttree->child.push_back(node);
                }
                LEXDEL;
                if (lexlist.at(0).word != "," && lexlist.at(1).word != "endstruct")
                {
                    err(RANC, "',' expected.");
                    exit_compiling(-14);
                }
                LEXDEL;
            }
            else if (lexlist.at(0).type == lextype::tag) // tag开头的是有名成员
            {
                if (lexlist.at(1).word != "#")
                {
                    err(RANC, "Member type undefined.");
                    exit_compiling(-12);
                }
                if (!(lexlist.at(2).type != lextype::keyword || lexlist.at(2).type != lextype::tag))
                {
                    err(RANC, "Unexpected type.");
                    exit_compiling(-13);
                }
                syntax_tree node = new StTree;
                {
                    node->father = sttree;
                    node->type = syntax::__tag;
                    node->content = lexlist.at(0).word;
                    node->content_discription = lexlist.at(2).word;
                    sttree->child.push_back(node);
                }
                LEXDEL;
                LEXDEL;
                if (node->content_discription == "addr") //处理addr类型特殊情况
                {
                    if (lexlist.at(1).word != "(" || lexlist.at(3).word != ")")
                    {
                        err(RANC, "Type definition needed after addr type.");
                        exit_compiling(-15);
                    }
                    node->content_discription += std::string("(") + lexlist.at(2).word + ")";
                    LEXDEL;
                    LEXDEL;
                    LEXDEL;
                }
                LEXDEL;
                if (lexlist.at(0).word != "," && lexlist.at(1).word != "endstruct")
                {
                    err(RANC, "',' expected.");
                    outputList(lexlist);
                    exit_compiling(-14);
                }
                LEXDEL;
            }
            else
            {
                err(RANC, "Struct definition nedded.");
                exit_compiling(-11);
            }
            membercount++;
        }
        sttree = sttree->father;
    }

    void do_make_express(syntax_tree sttree, std::vector<pair> &lexlist)
    { //TODO构建表达式
    }

    void make_express(syntax_tree sttree, std::vector<pair> &lexlist)
    {
        std::vector<pair> expression;
        while (operators.find(lexlist.at(0).word) != std::string::npos)
        {
            expression.push_back(lexlist.at(0));
            LEXDEL;
        }
        LEXDEL;
        do_make_express(sttree, expression);
    }

    void make_function(syntax_tree sttree, std::vector<pair> &lexlist)
    {
        LEXDEL;
        if (lexlist.at(0).type != lextype::tag)
        {
            err(RANC, "Function name needed.");
            exit_compiling(-12);
        }
        syntax_tree node = new StTree;
        {
            node->father = sttree;
            node->content = ":";
            node->content_discription = "def";
            node->type = syntax::__block;
            sttree->child.push_back(node);
        }
        sttree = node;
        {
            syntax_tree funcdesc = new StTree;
            {
                funcdesc->father = sttree;
                funcdesc->type = syntax::__tag;
                funcdesc->content = lexlist.at(0).word;
                funcdesc->content_discription = nullptr;
                sttree->child.push_back(funcdesc);
            }
            LEXDEL;
            if (lexlist.at(0).type != lextype::__operator)
            {
                err(RANC, "Arguments list needed.");
                exit_compiling(-13);
            }
            //TODO开始读取参数列表，并在读取参数列表后检查并确定返回类型
        }
        sttree = sttree->father;
        export_flag = false;
    }
};
