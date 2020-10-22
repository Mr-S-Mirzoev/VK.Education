#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <sys/types.h>
#include <vector>

class Process
{
    pid_t _pid;
    int _fd_in, _fd_out;
public:
    explicit Process(const std::string& path, const std::vector <std::string>& args);
    ~Process();

    size_t write(const void* data, size_t len);
    void writeExact(const void* data, size_t len);
    size_t read(void* data, size_t len);
    void readExact(void* data, size_t len);

    void closeStdin();

    void close();

    int return_status() const;
};

#endif