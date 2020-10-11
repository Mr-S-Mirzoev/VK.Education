#ifndef BASE_H
#define BASE_H

#include <string>
#include <vector>

typedef int level_t;

namespace log {
    enum LevelNo{
        NIL, // Nil value to define an error in passed Level Number

        DEBUG,
        INFO,
        WARNING,
        ERROR,

        QUANTITY // The constant to know  now many levels do we have
    };

    class Level {
        level_t _level;
    public:
        Level(level_t level);
        level_t to_int () const;
        bool allowed(Level checked);
        std::string to_string() const;
    };

    class Message {
        std::string _text;
        Level _level;
    public:
        Message(const std::string &message, Level level);
        Level get_level() const;
        std::string get_text() const;
    };

    class BaseLogger {
    protected:
        Level _level;
        std::vector <Message> _text_log;
    public:
        BaseLogger ();
        int debug(const std::string &message);
        int info(const std::string &message);
        int warning(const std::string &message);
        int error(const std::string &message);
        void set_level(Level level);
        Level level();
        virtual void flush() = 0;
        void log(const std::string &message, Level level);
    };
};

#endif