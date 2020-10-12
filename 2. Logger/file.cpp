#include "file.hpp"

namespace log {
    FileLogger::FileLogger(std::ofstream &&file): _file(std::move(file)) {}
    FileLogger::FileLogger(const std::string &path): _file(path) {}
    void FileLogger::flush() {
        for (auto &val : _text_log) {
            if (_level.allowed(val.get_level())) {
                _file << val.get_level().to_string() << " " << val.get_text() << std::endl;
            }
        }
        _text_log.clear();
    }
};