#ifndef LOG_HH
#define LOG_HH

namespace ran
{

    void log(std::string exec, std::string context);

    void err(std::string exec, std::string context);

    void fatal(std::string exec, std::string context);
};

#endif
