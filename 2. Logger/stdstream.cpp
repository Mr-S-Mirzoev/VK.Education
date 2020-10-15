#include <iostream>
#include "stdstream.hpp"

namespace log {
    StdOutLogger::StdOutLogger() {
        pr_debug("StdOutLogger()");
    }
    void StdOutLogger::flush() {
        for (auto &val : _text_log) {
            if (_level.allowed(val.get_level())) {
                std::cout << val.get_level().to_string() << " " << val.get_text() << std::endl;
            }
        }
        _text_log.clear(); // no except
    }
    StdOutLogger::~StdOutLogger () { 
        flush(); 
        pr_debug("~StdOutLogger()");
    }

    StdErrLogger::StdErrLogger() {
        pr_debug("StdErrLogger()");
    }
    void StdErrLogger::flush() {
        for (auto &val : _text_log) {
            if (_level.allowed(val.get_level())) {
                std::cerr << val.get_level().to_string() << " " << val.get_text() << std::endl;
            }
        }
        _text_log.clear(); // no except
    }
    StdErrLogger::~StdErrLogger() { 
        flush(); 
        pr_debug("~StdErrLogger()");
    }
}