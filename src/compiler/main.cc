/**
 * @file main.cc
 * @author pointer-to-bios
 * @brief 编译器
 * @version 0.1
 * @date 2022-05-14
 *
 * @copyright Copyright (c) 2022 Random World Studio
 *
 */

#include <iostream>
#include <fstream>

#include "../global/log.hh"

#include "maketree.hh"

std::string code;

std::string read_file(std::ifstream &); //读取文件

/**
 * @brief 主函数
 * 
 * @param argc 
 * @param argv 参数共两项：第一项是输入文件，第二项是输出文件
 * @return int 
 */
int main(int argc, char **argv)
{
    if (argc == 1) //缺参数直接报错
    {
        ran::fatal(RANC, "no input file.");
        exit_compiling(-1);
    }
    //打开文件
    std::ifstream file;
    file.open(argv[1], std::ios::in);
    code = read_file(file); //读取
    file.close();
    ran::log(RANC, "Reading source code succeeded.");

    ran::log(RANC, "Start compiling...");
    ran::make_tree(code);//生成语法树
    ran::log(RANC, "Compiling succeeded.");
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
