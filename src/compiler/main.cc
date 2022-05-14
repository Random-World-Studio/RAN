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

std::string code;

void exit_compiling(int);               //编译结束函数
std::string read_file(std::ifstream &); //读取文件

int main(int argc, char **argv)
{
    if (argc == 1) //缺参数直接报错
    {
        ran::fatal("ranc", "no input file.");
        exit_compiling(-1);
    }
    //打开文件
    std::ifstream file;
    file.open(argv[1], std::ios::in);
    code = read_file(file);//读取
    file.close();
    std::cout << code << std::endl;
}

void exit_compiling(int exit_num)
{
    ran::log("ranc", "compiling terminated.");
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
