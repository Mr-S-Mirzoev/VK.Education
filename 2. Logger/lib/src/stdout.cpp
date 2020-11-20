#include <iostream>
#include "stdout.hpp"

namespace log {
    StdOutLogger::StdOutLogger() {
        pr_debug("StdOutLogger()");
        _outputter = &std::cout;
    }

    StdOutLogger::~StdOutLogger () { 
        flush(); 
        pr_debug("~StdOutLogger()");
    }
}