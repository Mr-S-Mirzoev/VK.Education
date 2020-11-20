#ifndef LOGUTILS_H
#define LOGUTILS_H

#include <string>
#include "tools.hpp"

namespace log {
    void init_with_file_logger(const std::string &path);
    void init_with_stdout();
    void init_with_stderr();
    void debug(const std::string &message);
    void info(const std::string &message);
    void warning(const std::string &message);
    void error(const std::string &message);
    void set_level(int level);
    int level();
    void flush();
}

#endif