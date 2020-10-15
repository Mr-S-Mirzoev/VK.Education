#include "log_utils.hpp"
#include <iostream>

int main() {
/*
    log::FileLogger lg("log.txt");
    lg.set_level(log::WARNING);
    lg.debug("hello");
    lg.error("world");
    lg.info("I am");
    lg.warning("the lord");
    lg.flush();
*/
/*
    log::StdOutLogger lg;
    lg.set_level(log::WARNING);
    lg.debug("hello");
    lg.error("world");
    lg.info("I am");
    lg.warning("the lord");
    lg.flush();
*/
/*
    log::StdErrLogger lg;
    lg.set_level(log::WARNING);
    lg.debug("hello");
    lg.error("world");
    lg.info("I am");
    lg.warning("the lord");
    lg.flush();
*/
    log::init_with_stdout();
    log::debug("hello");
    log::error("world");
    log::info("I am");
    log::warning("the lord");
    log::flush();
    log::init_with_file_logger("out.txt");
    log::debug("heyya");
    log::error("people");
    log::info("here comes");
    log::warning("the lord");
}