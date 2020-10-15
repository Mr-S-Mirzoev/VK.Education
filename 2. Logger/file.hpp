#ifndef FILE_H
#define FILE_H

#include "base.hpp"
#include <fstream>

namespace log {
    class FileLogger: public BaseLogger {
        std::ofstream _file;
    public:
        FileLogger (std::ofstream &&file);
        FileLogger (const std::string &path);
        void flush() override;
        ~FileLogger () override;
    };
};

#endif