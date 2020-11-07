#include <iostream>
#include "stderr.hpp"

namespace log {
    StdErrLogger::StdErrLogger() {
        pr_debug("StdErrLogger()");
        _outputter = &std::cerr;
    }

    StdErrLogger::~StdErrLogger() { 
        pr_debug("~StdErrLogger()");
    }
}