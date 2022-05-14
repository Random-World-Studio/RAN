/*
main.cc
只接受输入文件并编译
*/

#include <iostream>
#include <fstream>

std::string code;

void exit_compiling(int);//编译结束函数
std::string read_file(std::ifstream &);//读取文件

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        std::cerr << "ranc: \033[31m\033[1mfatal: \033[0m"
                  << "no input file." << std::endl;
        exit_compiling(-1);
    }
    std::ifstream file;
    file.open(argv[1]);
    code = read_file(file);
    file.close();
    std::cout << code << std::endl;
}

void exit_compiling(int exit_num)
{
    std::cout << "compiling terminated." << std::endl;
    exit(exit_num);
}

std::string read_file(std::ifstream &file)
{
    std::string src = "", tmp;
    while (!file.eof())
    {
        getline(file, tmp);
        tmp += " ";
        src += tmp;
    }
    return src;
}
