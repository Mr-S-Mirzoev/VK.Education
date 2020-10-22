#ifndef STD_ERROR_H
#define STD_ERROR_H

#include "base.hpp"

namespace log {
    class StdErrLogger: public BaseLogger {
    public:
        StdErrLogger ();
        void flush() override;

        ~StdErrLogger () override;
    };
};

#endif