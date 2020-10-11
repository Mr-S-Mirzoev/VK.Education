#include "base.hpp"

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

    Message::Message(const std::string &message, Level level): 
        _text(message), _level(level) {}

    Level Message::get_level() const {
        return _level;
    }

    std::string Message::get_text() const {
        return _text;
    }

/* *** *** *** *** *** */

    BaseLogger::BaseLogger(): _level(NIL) {}

    int BaseLogger::debug(const std::string &message) {
        log(message, DEBUG);
    }

    int BaseLogger::error(const std::string &message) {
        log(message, ERROR);
    }

    int BaseLogger::info(const std::string &message) {
        log(message, INFO);
    }

    int BaseLogger::warning(const std::string &message) {
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