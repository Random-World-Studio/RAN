#include "compilerdef.hh"

void exit_compiling(int exit_num)
{
    ran::log(RANC, "compiling terminated.");
    exit(exit_num);
}