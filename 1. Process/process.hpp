#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <unistd.h>

class Process
{
    pid_t pid;
    static std::string exec_name(const std::string& full_path);
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