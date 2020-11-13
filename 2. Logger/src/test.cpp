#include "log_utils.hpp"
#include "file.hpp"
#include "stderr.hpp"
#include "stdout.hpp"
#include "test.hpp"

int main() {
    TEST("Testing FileLogger with WARNING level", 0, {
        log::FileLogger lg("test0-log.txt");
        lg.set_level(log::WARNING);
        lg.debug("I'm a debugger");
        lg.info("I'm an informer");
        lg.warning("I'm the warning maker");
        lg.error("Trouble (error) maker");
        lg.flush();
    })

    TEST("Testing StdOutLogger with INFO level", 1, {
        log::StdOutLogger lg;
        lg.set_level(log::INFO);
        lg.debug("I'm a debugger");
        lg.info("I'm an informer");
        lg.warning("I'm the warning maker");
        lg.error("Trouble (error) maker");
        lg.flush();
    })

    TEST("Testing StdErrLogger with ERROR level", 2, {
        log::StdOutLogger lg;
        lg.set_level(log::ERROR);
        lg.debug("I'm a debugger");
        lg.info("I'm an informer");
        lg.warning("I'm the warning maker");
        lg.error("Trouble (error) maker");
        lg.flush();
    })

    TEST("Testing log utilities with StdOut", 3, {
        log::init_with_stdout();
        log::debug("I'm a debugger");
        log::info("I'm an informer");
        log::warning("I'm the warning maker");
        log::error("Trouble (error) maker");
        log::flush();
    })

    TEST("Testing log utilities with StdOut and File", 4, {
        log::init_with_stdout();
        log::debug("I'm a debugger");
        log::info("I'm an informer");
        log::warning("I'm the warning maker");
        log::error("Trouble (error) maker");
        log::flush();
        log::init_with_file_logger("test4-log.txt");
        log::debug("heyya");
        log::info("here comes");
        log::warning("the lord");
        log::error("people");
    })
}