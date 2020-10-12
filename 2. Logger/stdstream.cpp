#include <iostream>
#include "stdstream.hpp"

namespace log {
    StdOutLogger::StdOutLogger() {}
    void StdOutLogger::flush() {
        for (auto &val : _text_log) {
            if (_level.allowed(val.get_level())) {
                std::cout << val.get_level().to_string() << " " << val.get_text() << std::endl;
            }
        }
        _text_log.clear();
    }

    StdErrLogger::StdErrLogger() {}
    void StdErrLogger::flush() {
        for (auto &val : _text_log) {
            if (_level.allowed(val.get_level())) {
                std::cerr << val.get_level().to_string() << " " << val.get_text() << std::endl;
            }
        }
        _text_log.clear();
    }
}