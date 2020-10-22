#include "file.hpp"

namespace log {
    FileLogger::FileLogger(std::ofstream &&file): _file(std::move(file)) {
        pr_debug("FileLogger(file)");
        _outputter = (&_file);
    }
    FileLogger::FileLogger(const std::string &path): _file(path) {
        pr_debug("FileLogger(path)");
        _outputter = (&_file);
    }
    void FileLogger::flush() {
        _file.flush();
    }

    FileLogger::~FileLogger() {
        flush();
        pr_debug("~FileLogger()");
    }
};