/**
 * @file main.cc
 * @author pointer-to-bios
 * @brief 接受文件并预处理
 * 包括移除注释、去掉多余空格、去掉多余分号以及所有换行
 * @version 0.1
 * @date 2022-05-14
 *
 * @copyright Copyright (c) 2022 Random World Studio
 *
 */

#include <iostream>
#include <fstream>

#include "../global/log.hh"
#include "../global/crlf.hh"
#include "../global/puncutation.hh"

const std::string RANP =  "ran preprocess";

std::string code;

void exit_compiling(int);               //编译结束函数
std::string read_file(std::ifstream &); //读取文件

void preprocess(); //预处理

int main(int argc, char **argv)
{
    if (argc == 1) //缺参数直接报错
    {
        ran::fatal(RANP, "no input file.");
        exit_compiling(-1);
    }
    //读取源文件
    ran::log(RANP, std::string("Reading source file\"") + argv[1] + "\"...");
    std::ifstream file;
    file.open(argv[1], std::ios::in);
    code = read_file(file); //读取
    file.close();
    ran::log(RANP, "Succeeded reading file.");

    preprocess(); //预处理

    //输出预处理好的源码
    std::ofstream ofile;
    ofile.open(std::string(argv[1]) + ".pre", std::ios::out);
    ofile << code;
    ofile.close();
    ran::log(RANP, std::string("Succeeded preprocess file \"") + argv[1] + "\" to \"" + argv[1] + ".pre\".");
}

void exit_compiling(int exit_num)
{
    ran::log(RANP, "preprocessing terminated.");
    exit(exit_num);
}

std::string read_file(std::ifstream &file)
{
    std::string src = "";
    char tmp;
    while (!file.eof())
    {
        file.read(&tmp, 1);
        src += tmp;
    }
    return src;
}

void preprocess()
{
    ran::log(RANP, "Preprocessing...");
    bool instring = false;
    for (int i = 0; i < code.length(); i++)
    {
        if (code[i] == '\"')
        {
            instring = !instring;
        }
        // //单行注释
        if (code[i] == '/' && code[i + 1] == '/')
        {
            int x = i + 2;
            while ((code[x] != NEWLINE) && x < code.length())
            {
                x++;
            }
            code.erase(i, x - i);
        }
    }
    instring = false;
    for (int i = 0; i < code.length(); i++)
    {
        if (code[i] == '\"')
        {
            instring = !instring;
        }
        //删除多余空格、换行、缩进
        if (!instring)
        {
            if (code[i] == ' ' && code[i + 1] == ' ')
            {
                while (code[i] == ' ' && code[i + 1] == ' ')
                {
                    code.erase(i + 1, 1);
                }
            }
            if (code[i] == '\t' || code[i] == '\n')
            {
                while (code[i] == '\t' || code[i] == '\n')
                {
                    code.erase(i, 1);
                }
            }
        }
        // /* */多行注释
        if (code[i] == '/' && code[i + 1] == '*')
        {
            int x = i + 1;
            while (!((code[x - 1] == '*') && (code[x] == '/')) && x < code.length())
            {
                x++;
            }
            if (code[x - 1] == '*' && code[x] == '/')
            {
                code.erase(i, x + 1 - i);
            }
            else
            {
                ran::err("ranc", "Annotation not terminated until end of file.");
                exit_compiling(-2);
            }
        }
        //删除多余空格、换行、缩进
        if (!instring)
        {
            if (code[i] == ' ' && code[i + 1] == ' ')
            {
                while (code[i] == ' ' && code[i + 1] == ' ')
                {
                    code.erase(i + 1, 1);
                }
            }
            if (code[i] == '\t' || code[i] == '\n')
            {
                while (code[i] == '\t' || code[i] == '\n')
                {
                    code.erase(i, 1);
                }
            }
        }
    }
    //删除标点符号前后的空格
    for (int i = 0; i < code.length(); i++)
        if (puncutations.find(code[i]) != std::string::npos)
        {
            if (code[i + 1] == ' ')
                code.erase(i + 1, 1);
            if (i != 0 && code[i - 1] == ' ')
                code.erase(i - 1, 1);
        }
    ran::log(RANP, "Preprocessing terminated.");
}
