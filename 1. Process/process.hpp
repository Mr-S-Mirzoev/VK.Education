#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>
#include <iostream>

#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

//#define DEBUG

void sig_handler(int signal);

class Process
{
    pid_t _pid;
    bool _noexec = false;
    int fd1[2];
    int fd2[2];
    
    static std::vector<char*> arg_list(const std::string &name, const std::vector <std::string>& args);
    static std::string exec_name(const std::string& full_path);
public:
    explicit Process(const std::string& path, const std::vector <std::string>& args);
    ~Process();

    size_t write(const void* data, size_t len);
    void writeExact(const void* data, size_t len);
    size_t read(void* data, size_t len);
    void readExact(void* data, size_t len);

    void closeStdin();

    void close();

    bool exec_failed() const;
};

#endif