#include "maketree.hh"

#include "../global/log.hh"
#include "../global/puncutation.hh"

#include <vector>
#include <algorithm>

namespace ran
{

    enum lextype //词法类型
    {
        keyword,    //关键字
        area_start, //作用域起始
        area_end,   //作用域结束
        tag,        //符号
        __operator, //运算符
        number,     //数字
        string,     //字符串
        undefined,
    };

    struct pair //词法表元素
    {
        std::string word;
        lextype type;
    };

    std::vector<pair> lexy(std::string);

    void make_tree(std::string code)
    {
        ran::log(RANC, "Making gramma tree...");
        std::vector<pair> lexlist = lexy(code); //生成词法表
    }

    std::vector<pair> lexy(std::string code)
    {
        std::vector<pair> list;
        while (!code.empty())
        {
            if (puncutations.find(code[0]) != std::string::npos) //如果第一个字符是标点符号
            {
                if (relatedpunc.find(code[0]) == std::string::npos) //无关符号就直接擦掉
                {
                    code.erase(0, 1);
                }
                else
                { //有关符号加入词法列表
                    std::string str = std::string("" + code[0]);
                    code.erase(0, 1);
                    if (relatedpunc.find(code[0]) != std::string::npos)
                    {
                        str += std::string("" + code[0]);
                        code.erase(0, 1);
                    }
                    list.push_back({str, lextype::__operator});
                }
            }
            //现在第一个词一定是单词
            int count = 0;
            while (puncutations.find(code[count]) == std::string::npos)
                count++;
            std::string str = code.substr(0, count);
            code.erase(0, count);
            lextype t;
            if (std::find(keywords.begin(), keywords.end(), str) != keywords.end())
                t = lextype::keyword;
            else
                t = lextype::tag;
            list.push_back({str, t});
        }
    }
};
