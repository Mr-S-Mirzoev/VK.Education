#include <iostream>
#include "stdout.hpp"

namespace log {
    StdOutLogger::StdOutLogger() {
        pr_debug("StdOutLogger()");
    }
    void StdOutLogger::flush() {
        std::cout.flush();
    }
    void StdOutLogger::log(const std::string &message, Level level) {
        if (_level.allowed(level)) {
            std::cout << level.to_string() << " " << message << std::endl;
        }
    }

    StdOutLogger::~StdOutLogger () { 
        flush(); 
        pr_debug("~StdOutLogger()");
    }
}