#ifndef STD_STREAM_H
#define STD_STREAM_H

#include "base.hpp"

namespace log {
    class StdOutLogger: public BaseLogger {
    public:
        StdOutLogger ();
        void flush() override;
        ~StdOutLogger () override;
    };

    class StdErrLogger: public BaseLogger {
    public:
        StdErrLogger ();
        void flush() override;
        ~StdErrLogger () override;
    };
};

#endif