#ifndef STD_ERROR_H
#define STD_ERROR_H

#include "base.hpp"

namespace log {
    class StdErrLogger: public BaseLogger {
        void log(const std::string &message, Level level) override;
    public:
        StdErrLogger ();
        void flush() override;

        ~StdErrLogger () override;
    };
};

#endif