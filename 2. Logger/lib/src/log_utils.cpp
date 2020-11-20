#include "log_utils.hpp"
#include "logger.hpp"
#include "file.hpp"
#include "stderr.hpp"
#include "stdout.hpp"
#include "tools.hpp"

namespace log {

    void init_with_file_logger(const std::string &path) {
        pr_debug("log::init_with_file_logger");
        std::unique_ptr<log::BaseLogger> ptr {new FileLogger(path)};
        log::Logger::get_instance()->set_global_logger(ptr); // noexcept
    }
    void init_with_stdout() {
        pr_debug("log::init_with_stdout");
        std::unique_ptr<log::BaseLogger> ptr {new StdOutLogger};
        log::Logger::get_instance()->set_global_logger(ptr);
    }
    void init_with_stderr() {
        pr_debug("log::init_with_stderr");
        std::unique_ptr<log::BaseLogger> ptr {new StdErrLogger};
        log::Logger::get_instance()->set_global_logger(ptr);
    }
    void debug(const std::string &message) {
        log::Logger::get_instance()->get_global_logger()->debug(message);
    }
    void info(const std::string &message) {
        log::Logger::get_instance()->get_global_logger()->info(message);
    }
    void warning(const std::string &message) {
        log::Logger::get_instance()->get_global_logger()->warning(message);
    }
    void error(const std::string &message) {
        log::Logger::get_instance()->get_global_logger()->error(message);
    }
    void set_level(int level) {
        log::Logger::get_instance()->get_global_logger()->set_level(level);
    }
    int level() {
        return log::Logger::get_instance()->get_global_logger()->level();
    }
    void flush() {
        pr_debug("log::flush");
        log::Logger::get_instance()->get_global_logger()->flush();
    }
}