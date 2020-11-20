#include "logger.hpp"
#include "tools.hpp"
#include <iostream>

namespace log {
    Logger* const Logger::_instance {new Logger};

    Logger::Logger(): _global_logger (nullptr) {
        pr_debug("Logger()");
    }

    Logger::~Logger() {
        pr_debug("~Logger()");
    }

    Logger* const Logger::get_instance() {
        if (Logger::_instance == nullptr) {
            pr_debug("No instance");
        }
        return Logger::_instance; // no except
    }

    void Logger::set_global_logger(std::unique_ptr<BaseLogger> &other) {
        int prevLevel = ERROR;
        if (_global_logger) {
            _global_logger->flush();
            prevLevel = _global_logger->level();
        }
        _global_logger.swap(other);
        _global_logger->set_level(prevLevel);
    };
    BaseLogger* Logger::get_global_logger() {
        if (_global_logger)
            return _global_logger.get(); // no except
        else
            throw std::logic_error("No logger initialization took place.");
    }
}