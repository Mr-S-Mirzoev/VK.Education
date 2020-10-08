#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>

//#define DEBUG
#define CHILD(pid) (pid == 0)
#define POSIX_ERROR(ret_val) (ret_val < 0)

static std::vector<char*> arg_list(const std::string &name, const std::vector <std::string>& args);
static std::string exec_name(const std::string& full_path);

class Process
{
    pid_t _pid;
    int fd_in, fd_out;
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