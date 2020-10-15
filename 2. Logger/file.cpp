#include "file.hpp"

namespace log {
    FileLogger::FileLogger(std::ofstream &&file): _file(std::move(file)) {
        pr_debug("FileLogger(file)");
    }
    FileLogger::FileLogger(const std::string &path): _file(path) {
        pr_debug("FileLogger(path)");
    }
    void FileLogger::flush() {
        for (auto &val : _text_log) {
            if (_level.allowed(val.get_level())) {
                _file << val.get_level().to_string() << " " << val.get_text() << std::endl;
            }
        }
        _text_log.clear();
    }
    FileLogger::~FileLogger() {
        flush();
        pr_debug("~FileLogger()");
    }
};