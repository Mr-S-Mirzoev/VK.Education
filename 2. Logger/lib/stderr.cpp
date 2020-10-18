#include <iostream>
#include "stderr.hpp"

namespace log {
    StdErrLogger::StdErrLogger() {
        pr_debug("StdErrLogger()");
    }
    void StdErrLogger::flush() {
        std::cerr.flush();
    }
    void StdErrLogger::log(const std::string &message, Level level) {
        if (_level.allowed(level)) {
            std::cerr << level.to_string() << " " << message << std::endl;
        }
    }

    StdErrLogger::~StdErrLogger() { 
        flush(); 
        pr_debug("~StdErrLogger()");
    }
}