#include <iostream>
#include "stderr.hpp"

namespace log {
    StdErrLogger::StdErrLogger() {
        pr_debug("StdErrLogger()");
        _outputter = &std::cerr;
    }
    void StdErrLogger::flush() {
        std::cerr.flush();
    }

    StdErrLogger::~StdErrLogger() { 
        flush(); 
        pr_debug("~StdErrLogger()");
    }
}