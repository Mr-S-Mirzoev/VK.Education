#ifndef STD_OUT_H
#define STD_OUT_H

#include "base.hpp"

namespace log {
    class StdOutLogger: public BaseLogger {
    public:
        StdOutLogger ();
        void flush() override;

        ~StdOutLogger () override;
    };
};

#endif