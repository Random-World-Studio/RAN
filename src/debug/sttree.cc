#include "sttree.hh"

#include <iostream>

namespace ran
{
    std::string st[] = {
        "block",
        "expression",
        "number",
        "tag",
    };

    void outputTree(syntax_tree tree, int dpt, bool b, bool b1)
    {
        if (dpt)
        {
            for (int i = 0; i < dpt - 1; i++)
            {
                std::cout << '\t';
                if (b1)
                    std::cout << "│";
            }
            if (dpt - 1 >= 0)
            {
                if (b)
                    std::cout << '\t' << "├──";
                else
                    std::cout << '\t' << "└──";
            }
        }
        std::cout << "[" << st[tree->type] << "](\""
                  << tree->content << "\":"
                  << tree->content_discription << ")" << std::endl;
        for (syntax_tree stt : tree->child)
            outputTree(stt, dpt + 1, stt != *(tree->child.crbegin()), b);
    }

    std::string lst[] = {
        "keyword",
        "tag",
        "__operator",
        "number",
        "string",
        "undefined",
    };

    void outputList(std::vector<pair> list)
    {
        for (pair p : list)
        {
            std::cout << "\"" << p.word << "\"[" << lst[p.type] << "]" << std::endl;
        }
    }
};
