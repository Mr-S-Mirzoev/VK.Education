#include "tools.hpp"
#include <iostream>

namespace log {

    void pr_debug(const std::string &s) {
        #ifndef NDEBUG
        std::cerr << s << std::endl;
        #endif
    }
};