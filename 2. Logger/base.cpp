#include "base.hpp"

namespace log {

    BaseLogger::BaseLogger(): _level(NIL) {}

    void BaseLogger::debug(const std::string &message) {
        log(message, DEBUG);
    }

    void BaseLogger::error(const std::string &message) {
        log(message, ERROR);
    }

    void BaseLogger::info(const std::string &message) {
        log(message, INFO);
    }

    void BaseLogger::warning(const std::string &message) {
        log(message, WARNING);
    }

    void BaseLogger::set_level(Level level) {
        _level = level;
    }

    Level BaseLogger::level() {
        return _level;
    }

    void BaseLogger::log(const std::string &message, Level level) {
        _text_log.push_back(Message(message, level));
    }
};