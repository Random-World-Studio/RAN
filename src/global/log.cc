#ifndef LOG_HH
#define LOG_HH

#include <iostream>

namespace ran
{

    void log(std::string exec, std::string context)
    {
        std::clog << "\033[32m[" << exec << "][log]\033[0m " << context << std::endl;
    }

    void err(std::string exec, std::string context)
    {
        std::cerr << "\033[32m[" << exec << "]\033[31m[error]\033[0m " << context << std::endl;
    }

    void fatal(std::string exec, std::string context)
    {
        err(exec, std::string("\033[31m\033[1m[fatal]\033[0m ") + context);
    }
};

#endif
