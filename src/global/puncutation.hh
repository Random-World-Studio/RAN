#ifndef PUNCUTATION_HH
#define PUNCUTATION_HH

#include <iostream>
#include <vector>

std::string puncutations(",./<>?;\':\"[]\\{}|`-=~!@#$%^&*()+ ");

std::string operators("<>?:[]~!@#%^&*-=+,.();");
std::string ex_ope("=&|");

std::vector<std::string> keywords = {
    "struct",
    "endstruct",
    "true",
    "false",
    "if",
    "endif",
    "while",
    "endwhile",
    "for",
    "endfor",
    "return",
    "def",
    "enddef",
    "modname",
    "import",
    "export",
    "break",
    "continue",
    "int",
    "uint",
    "short",
    "ushort",
    "char",
    "byte",
    "float",
    "ufloat",
    "str",
    "bool",
    "addr",
    "asm"};

#endif
