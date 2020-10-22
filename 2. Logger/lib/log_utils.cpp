#include "log_utils.hpp"
#include "logger.hpp"
#include "file.hpp"
#include "stderr.hpp"
#include "stdout.hpp"
#include "tools.hpp"

namespace log {

    void init_with_file_logger(const std::string &path) {
        pr_debug("log::init_with_file_logger");
        std::ofstream outFile(path);
        log::Logger::get_instance()->set_global_logger(new FileLogger(std::move(outFile))); // noexcept
    }
    void init_with_stdout() {
        pr_debug("log::init_with_stdout");
        log::Logger::get_instance()->set_global_logger(new StdOutLogger);
    }
    void init_with_stderr() {
        pr_debug("log::init_with_stderr");
        log::Logger::get_instance()->set_global_logger(new StdErrLogger);
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