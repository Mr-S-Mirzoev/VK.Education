#include "file.hpp"
#include "stdstream.hpp"

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
    log::StdErrLogger lg;
    lg.set_level(log::WARNING);
    lg.debug("hello");
    lg.error("world");
    lg.info("I am");
    lg.warning("the lord");
    lg.flush();
}