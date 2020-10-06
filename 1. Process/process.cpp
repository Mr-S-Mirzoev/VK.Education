#include "process.hpp"

Process::Process(const std::string& path) {
    pid = fork();
    if (!pid) {
        execl(path.c_str(), Process::exec_name(path).c_str(), nullptr);
    }
}

