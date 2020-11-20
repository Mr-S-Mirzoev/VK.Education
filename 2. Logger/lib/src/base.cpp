#include "base.hpp"
#include "tools.hpp"

#include <iostream>

namespace log {

    BaseLogger::BaseLogger(): _level(ERROR), _outputter(nullptr) {
        pr_debug("BaseLogger()");
    }

    void BaseLogger::debug(const std::string &message) const {
        log(message, "[debug] :", DEBUG);
    }

    void BaseLogger::error(const std::string &message) const {
        log(message, "[error] :", ERROR);
    }

    void BaseLogger::info(const std::string &message) const {
        log(message, "[info] :", INFO);
    }

    void BaseLogger::warning(const std::string &message) const {
        log(message, "[warning] :", WARNING);
    }

    void BaseLogger::set_level(int level) {
        _level = level;
    }

    int BaseLogger::level() {
        return _level;
    }
    
    BaseLogger::~BaseLogger() {
        pr_debug("~BaseLogger()");
    }

    void BaseLogger::log(const std::string &message, const std::string &level_name, int level) const {
        if (_level <= level) {
            *_outputter << level_name << " " << message << std::endl;
        }
    }

    void BaseLogger::flush() {
        _outputter->flush();
    }
};