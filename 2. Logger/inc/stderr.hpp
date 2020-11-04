#ifndef STD_ERROR_H
#define STD_ERROR_H

#include "base.hpp"

namespace log {
    class StdErrLogger: public BaseLogger {
    public:
        StdErrLogger ();
        ~StdErrLogger () override;
    };
};

#endif