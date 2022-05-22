#ifndef LEX_HH
#define LEX_HH

#include "compilerdef.hh"

#include "../global/log.hh"

#include <iostream>
#include <vector>

namespace ran
{

    enum lextype //词法类型
    {
        keyword,    //关键字
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
};

#endif
