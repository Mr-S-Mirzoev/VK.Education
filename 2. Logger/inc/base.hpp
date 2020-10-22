#ifndef BASE_H
#define BASE_H

#include <string>
#include <vector>
#include <memory>

#include "tools.hpp"

namespace log {
    class BaseLogger {
    protected:
        int _level;
        BaseLogger();
        std::ostream *_outputter;
    public:
        static BaseLogger& getInstance();

        void debug(const std::string &message);
        void info(const std::string &message);
        void warning(const std::string &message);
        void error(const std::string &message);
        void set_level(int level);
        int level();
        virtual void flush() = 0;
        virtual ~BaseLogger();
    private:
        virtual void log(const std::string &message, const std::string &level_name, int level);
        static bool _instanceFlag;
        static std::unique_ptr<BaseLogger> _ptr;
    };
};

#endif