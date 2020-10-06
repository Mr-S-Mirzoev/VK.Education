#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <sys/wait.h>
#include <signal.h>

//#define DEBUG

void sig_handler(int signal) {
    exit(0);
}

class Process
{
    pid_t _pid;
    bool _noexec = false;

    static std::string exec_name(const std::string& full_path) {
        std::size_t pos = full_path.rfind('/');
        if (pos == std::string::npos)
            return full_path;
        return full_path.substr(pos);
    }
public:
    explicit Process(const std::string& path);
    ~Process();

    size_t write(const void* data, size_t len);
    void writeExact(const void* data, size_t len);
    size_t read(void* data, size_t len);
    void readExact(void* data, size_t len);

    void closeStdin();

    void close();
};

#endif