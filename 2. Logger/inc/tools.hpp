#ifndef TOOLS_H
#define TOOLS_H

#include <string>

namespace log {
    enum LevelNo{
        DEBUG,
        INFO,
        WARNING,
        ERROR,
    };

    void pr_debug(const std::string &s);
};

#endif