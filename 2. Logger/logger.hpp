#ifndef LOGGER_SINGLETON_H
#define LOGGER_SINGLETON_H

#include <memory>
#include "base.hpp"

namespace log {
    class Logger
    {
    private:
        Logger();
        static bool _has_instance;
        static Logger *_instance;
        static std::unique_ptr<BaseLogger> _global_logger;
    public:
        ~Logger();
        Logger(const Logger&) = delete;
        Logger& operator= (const Logger) = delete;
    private:
        static Logger& get_instance();
        static void set_global_logger(BaseLogger);
        static BaseLogger* get_global_logger();
    };    
};

#endif