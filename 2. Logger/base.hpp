#ifndef BASE_H
#define BASE_H

#include <string>
#include <vector>

#include "tools.hpp"

namespace log {
    class BaseLogger {
    protected:
        Level _level;
        std::vector <Message> _text_log;
        BaseLogger();
    public:
        static BaseLogger& getInstance();
        ~BaseLogger();

        void debug(const std::string &message);
        void info(const std::string &message);
        void warning(const std::string &message);
        void error(const std::string &message);
        void set_level(Level level);
        Level level();
        virtual void flush() = 0;
        void log(const std::string &message, Level level);
    private:
        static bool _instanceFlag;
        static std::unique_ptr<BaseLogger> _ptr;
    };
};

#endif