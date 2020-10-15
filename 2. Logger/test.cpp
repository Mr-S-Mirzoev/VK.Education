#include "log_utils.hpp"
#include "file.hpp"
#include "stdstream.hpp"
#include "test.hpp"

int main() {
    TEST("Testing FileLogger with WARNING level", 0, {
        log::FileLogger lg("test0-log.txt");
        lg.set_level(log::WARNING);
        lg.debug("hello");
        lg.error("world");
        lg.info("I am");
        lg.warning("the lord");
        lg.flush();
    })

    TEST("Testing StdOutLogger with INFO level", 1, {
        log::StdOutLogger lg;
        lg.set_level(log::INFO);
        lg.debug("hello");
        lg.error("world");
        lg.info("I am");
        lg.warning("the lord");
        lg.flush();
    })

    TEST("Testing StdErrLogger with ERROR level", 2, {
        log::StdOutLogger lg;
        lg.set_level(log::ERROR);
        lg.debug("hello");
        lg.error("world");
        lg.info("I am");
        lg.warning("the lord");
        lg.flush();
    })

    TEST("Testing log utilities with StdOut", 3, {
        log::init_with_stdout();
        log::debug("hello");
        log::error("world");
        log::info("I am");
        log::warning("the lord");
        log::flush();
    })

    TEST("Testing log utilities with StdOut and File", 4, {
        log::init_with_stdout();
        log::debug("hello");
        log::error("world");
        log::info("I am");
        log::warning("the lord");
        log::flush();
        log::init_with_file_logger("test4-log.txt");
        log::debug("heyya");
        log::error("people");
        log::info("here comes");
        log::warning("the lord");
    })
}