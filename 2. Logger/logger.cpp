#include "logger.hpp"

namespace log {
    Logger::Logger()
    {
    }
    
    Logger::~Logger()
    {
    }

    Logger& Logger::get_instance() {
        if (!Logger::_has_instance) {
            Logger::_has_instance = true;
            Logger::_instance = new Logger;
        }
        return *Logger::_instance;
    }
}