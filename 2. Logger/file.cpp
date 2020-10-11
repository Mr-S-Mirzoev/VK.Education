#include "file.hpp"

namespace log {
    FileLogger::FileLogger(std::ofstream &file): _file(file) {}
    void FileLogger::flush() {
        for (auto &val : _text_log) {
            if (val.get_level().allowed(_level)) {
                _file << val.get_level().to_string() << " " << val.get_text() << std::endl;
            }
        }
    }
};