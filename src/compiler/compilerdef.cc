#include "compilerdef.hh"

void exit_compiling(int exit_num)
{
    ran::log(RANC, std::string("compiling terminated.") + std::to_string(exit_num));
    exit(exit_num);
}