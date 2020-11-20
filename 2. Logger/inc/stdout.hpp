#ifndef STD_OUT_H
#define STD_OUT_H

#include "base.hpp"

namespace log {
    class StdOutLogger: public BaseLogger {
    public:
        StdOutLogger ();
        ~StdOutLogger () override;
    };
};

#endif