#include "file.hpp"

namespace log {
    FileLogger::FileLogger(std::ofstream &&file): _file(std::move(file)) {
        pr_debug("FileLogger(file)");
    }
    FileLogger::FileLogger(const std::string &path): _file(path) {
        pr_debug("FileLogger(path)");
    }
    void FileLogger::flush() {
        _file.flush();
    }
    void FileLogger::log(const std::string &message, Level level) {
        if (_level.allowed(level)) {
            _file << level.to_string() << " " << message << std::endl;
        }
    }

    FileLogger::~FileLogger() {
        flush();
        pr_debug("~FileLogger()");
    }
};