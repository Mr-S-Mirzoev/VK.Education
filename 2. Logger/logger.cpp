#include "logger.hpp"
#include "tools.hpp"
#include <iostream>

namespace log {
    std::unique_ptr<Logger> Logger::_instance {nullptr};
    std::unique_ptr<BaseLogger> Logger::_global_logger {nullptr};

    Logger::Logger(){
        pr_debug("Logger()");
    }

    Logger::~Logger() {
        pr_debug("~Logger()");
    }

    Logger* Logger::get_instance() {
        if (Logger::_instance == nullptr) {
            pr_debug("No instance");
            Logger::_instance.reset(new Logger); // no except method
        }
        return Logger::_instance.get(); // no except
    }

    void Logger::set_global_logger(BaseLogger *other) {
        Level prevLevel = NIL;
        if (_global_logger) {
            _global_logger->flush();
            prevLevel = _global_logger->level();
        }
        _global_logger.reset(other);
        _global_logger->set_level(prevLevel);
    };
    BaseLogger* Logger::get_global_logger() {
        return _global_logger.get(); // no except
    }
}