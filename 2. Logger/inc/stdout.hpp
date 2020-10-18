#ifndef STD_OUT_H
#define STD_OUT_H

#include "base.hpp"

namespace log {
    class StdOutLogger: public BaseLogger {
        void log(const std::string &message, Level level) override;
    public:
        StdOutLogger ();
        void flush() override;

        ~StdOutLogger () override;
    };
};

#endif