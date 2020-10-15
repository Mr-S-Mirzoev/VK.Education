#include "log_utils.hpp"
#include "logger.hpp"
#include "file.hpp"
#include "stdstream.hpp"
#include "tools.hpp"

namespace log {
    void init_with_file_logger(const std::string &path) {
        pr_debug("log::init_with_file_logger");
        auto logger = log::Logger::get_instance();
        std::ofstream outFile(path);
        logger->set_global_logger(new FileLogger(std::move(outFile))); // noexcept
    }
    void init_with_stdout() {
        pr_debug("log::init_with_stdout");
        auto logger = log::Logger::get_instance();
        logger->set_global_logger(new StdOutLogger);
    }
    void init_with_stderr() {
        pr_debug("log::init_with_stderr");
        auto logger = log::Logger::get_instance();
        logger->set_global_logger(new StdErrLogger);
    }
    void debug(const std::string &message) {
        auto logger = log::Logger::get_instance();
        logger->get_global_logger()->debug(message);
    }
    void info(const std::string &message) {
        auto logger = log::Logger::get_instance();
        logger->get_global_logger()->info(message);
    }
    void warning(const std::string &message) {
        auto logger = log::Logger::get_instance();
        logger->get_global_logger()->warning(message);
    }
    void error(const std::string &message) {
        auto logger = log::Logger::get_instance();
        logger->get_global_logger()->error(message);
    }
    void set_level(Level level) {
        auto logger = log::Logger::get_instance();
        logger->get_global_logger()->set_level(level);
    }
    Level level() {
        auto logger = log::Logger::get_instance();
        return logger->get_global_logger()->level();
    }
    void flush() {
        pr_debug("log::flush");
        auto logger = log::Logger::get_instance();
        logger->get_global_logger()->flush();
    }
    void log(const std::string &message, Level level) {
        auto logger = log::Logger::get_instance();
        logger->get_global_logger()->log(message, level);
    }
}