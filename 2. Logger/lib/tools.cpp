#include "tools.hpp"
#include <iostream>

namespace log {

    Level::Level(level_t level) {
        if (level < QUANTITY && level > NIL)
            _level = level;
        else
            _level = NIL; // error
    }

    bool Level::allowed(Level checked) {
        Level accesible = _level;
        return (checked._level >= accesible._level);
    }

    level_t Level::to_int () const {
        return _level;
    }

    std::string Level::to_string() const {
        switch (_level)
        {
        case DEBUG:
            return "[debug]";
            break;
        case INFO:
            return "[info]";
            break;
        case WARNING:
            return "[warning]";
            break;
        case ERROR:
            return "[error]";
            break;

        case NIL:
        default:
            return "[wrong-message-level]";
            break;
        }
    }

/* *** *** *** *** *** */

    void pr_debug(const std::string &s) {
        #ifndef NDEBUG
        std::cerr << s << std::endl;
        #endif
    }
};