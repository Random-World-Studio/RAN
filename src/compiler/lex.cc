#include "lex.hh"

#include <algorithm>
#include <regex>

#include "../global/puncutation.hh"

namespace ran
{

    std::vector<pair> lexy(std::string code)
    {
        ran::log(RANC, "Producing a lexy list...");
        std::vector<pair> list;
        while (!code.empty())
        {
            if (puncutations.find(code[0]) == std::string::npos) //这是一个单词
            {
                int count = 0;
                while (puncutations.find(code[count]) == std::string::npos)
                    count++;
                std::string str = code.substr(0, count);
                lextype t = lextype::tag;
                if (std::find(keywords.begin(), keywords.end(), str) != keywords.end()) //匹配关键字
                    t = lextype::keyword;
                if (std::regex_match(str, std::regex("0?[x|b]?\\d+"))) //匹配数字
                    t = lextype::number;
                list.push_back({str, t});
                code.erase(0, count);
            }
            else if (code[0] == '\"') //字符串
            {
                int count = 1;
                while (code[count] != '\"')
                    count++;
                count++;
                list.push_back({code.substr(0, count), lextype::string});
                code.erase(0, count);
            }
            else
            {
                //匹配运算符
                bool b = false;
                std::string str("");
                for (int i = 0; i < operators.length(); i++)
                {
                    if (code[0] == operators[i])
                    {
                        str += code[0];
                        b = true;
                        break;
                    }
                }
                if (b)
                {
                    //匹配双字符运算符
                    code.erase(0, 1);
                    for (int i = 0; i < ex_ope.length(); i++)
                    {
                        if (code[0] == ex_ope[i])
                        {
                            str += code[0];
                            code.erase(0, 1);
                            break;
                        }
                    }
                    list.push_back({str, lextype::__operator});
                }
                else //无法匹配就扫描下一个
                    code.erase(0, 1);
            }
        }
        ran::log(RANC, "Lexy list produced.");
        return list;
    }
};
