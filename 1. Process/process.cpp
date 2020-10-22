#include "process.hpp"
#include "pipe2.hpp"

#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

static std::vector<char*> arg_list(std::string name, const std::vector <std::string>& args) {
    std::vector<std::string> args_copy{args};
    std::string name_copy{name};
    std::vector<char*> cstyle_args;
    cstyle_args.reserve(args.size() + 1);

    cstyle_args.push_back(name_copy.data());
    for (auto &arg : args_copy)
        cstyle_args.push_back(arg.data());
    cstyle_args.push_back(nullptr);
    
    return cstyle_args;
}

static std::string exec_name(const std::string& full_path) {
    std::size_t pos = full_path.rfind('/');
    if (pos == std::string::npos)
        return full_path;
    return full_path.substr(pos + 1);
}

static inline bool POSIX_ERROR(int ret_val) {
    return (ret_val < 0);
}

static inline void pr_string_debug (const std::string &s) {
#ifndef NDEBUG
    std::cerr << s << std::endl;
#endif
}

static inline void pr_inttype_debug (const std::string &s, int v) {
#ifndef NDEBUG
    std::cerr << s << v << std::endl;
#endif
}



// Process implementation

Process::Process(const std::string& path, const std::vector <std::string>& args) {
    int fd1[2];
    int fd2[2];

    int ret;

    ret = pipe2(fd1, 0);
    if (ret == -1) {
        pr_string_debug("Pipe1 initialization failed");
        return;
    }

    ret = pipe2(fd2, 0);
    if (ret == -1) {
        pr_string_debug("Pipe2 initialization failed");
        ::close(fd1[0]);
        ::close(fd1[1]);
        return;
    }

    int verif_fd[2];
    ret = pipe2(verif_fd, O_CLOEXEC);
    if (ret == -1) {
        std::cerr << "Exec verification pipe initialization failed" << std::endl;
        ::close(fd1[0]);
        ::close(fd1[1]);
        ::close(fd2[0]);
        ::close(fd2[1]);
        return;
    }

    pr_string_debug("Executing: " + path + " " + exec_name(path));
    _pid = fork();

    if (_pid == 0) {
        pr_string_debug("Forked off successfully");

        dup2(fd1[0], STDIN_FILENO);
        dup2(fd2[1], STDOUT_FILENO);

        ::close(fd1[0]);
        ::close(fd1[1]);
        ::close(fd2[0]);
        ::close(fd2[1]);

        // Forming EXECVP arguments list:
        std::string e_name = exec_name(path);
        std::vector<std::string> arg_list_copy{args};
        std::vector<char*> cstyle_args;
        cstyle_args.reserve(args.size() + 1);

        cstyle_args.push_back(e_name.data());
        for (auto &arg : arg_list_copy)
            cstyle_args.push_back(arg.data());
        cstyle_args.push_back(nullptr);

        execvp(path.c_str(), cstyle_args.data());

        pr_string_debug("EXECVP failed");

        exit(-1);
    } else if (POSIX_ERROR(_pid)) {
        ::close(fd1[0]);
        ::close(fd1[1]);
        ::close(fd2[0]);
        ::close(fd2[1]);
        ::close(verif_fd[0]);
        ::close(verif_fd[1]);

        pr_string_debug("Forking off failed");

        return;
    } else {
        ::close(verif_fd[1]);  // Attaching this action to logical part of forking off
    }

    char tmp;
    ssize_t size = ::read(verif_fd[0], &tmp, sizeof(tmp));
    ::close(verif_fd[0]);

    int status;
    pid_t pid_result = waitpid(_pid, &status, WNOHANG);
    pr_inttype_debug("PID: ", pid_result);
    pr_inttype_debug("Status: ", status);

    _fd_in = fd2[0];
    _fd_out = fd1[1];

    bool noexec = (pid_result != 0);
    if (noexec) {
        ::close(_fd_in);
        _fd_in = -1;
        ::close(_fd_out);
        _fd_out = -1;
        kill(_pid, SIGKILL);
        waitpid(_pid, &status, 0);
        throw(std::runtime_error("Execution of programm " + path + " failed"));
    }

    ::close(fd2[1]);
    ::close(fd1[0]);
}

Process::~Process() {
    int status;

    ::close(_fd_in);
    ::close(_fd_out);

    kill(_pid, SIGKILL);
    waitpid(_pid, &status, 0);
    pr_inttype_debug("Exit status of child process: ", WEXITSTATUS(status));
}

void Process::close() {
    int status;

    ::close(_fd_in);
    _fd_in = -1;
    ::close(_fd_out);
    _fd_out = -1;
    kill(_pid, SIGINT);
    waitpid(_pid, &status, 0);
}

void Process::closeStdin() {
    pr_string_debug("Trying to close Stdin from parent");
    ::close(_fd_out);
}

size_t Process::read(void* data, size_t len) {
    if (_fd_in == -1) 
        throw std::runtime_error("Reading failed due to the fact file is closed.");

    size_t ret_val = ::read(_fd_in, data, len);

    if (POSIX_ERROR(ret_val))
        throw std::runtime_error("Reading data failed");
    else if (!ret_val)
        pr_string_debug("Trying to read from a closed pipe");
    else
        pr_inttype_debug("Quantity of read bytes: ", ret_val);

    return ret_val;
}

void Process::readExact(void* data, size_t len) {
    char *sized_data = static_cast<char *>(data);

    size_t offset = 0;
    while (offset < len) {
        size_t bytes_read = read(sized_data + offset, len);
        pr_inttype_debug("Quantity of read bytes: ", bytes_read);
        if (bytes_read == 0)
            throw std::runtime_error("Error while reading");
        
        offset += bytes_read;
    }
}

size_t Process::write(const void* data, size_t len) {
    if (_fd_out == -1) 
        throw std::runtime_error("Writing failed due to the fact file is closed.");

    size_t ret_val = ::write(_fd_out, data, len);

    if (POSIX_ERROR(ret_val))
        throw std::runtime_error("Writing failed");

    pr_inttype_debug("Quantity of written bytes: ", ret_val);

    return ret_val;
}

void Process::writeExact(const void* data, size_t len) {
    size_t offset = 0;
    const char *sized_data = static_cast<const char *>(data);
    while (offset < len) {
        size_t bytes_written = write(sized_data + offset, len);
        pr_string_debug("Data: " + std::string(sized_data));
        pr_inttype_debug("Bytes written: ", bytes_written);
        offset += bytes_written;
    }
}

int Process::return_status() const {
    int status;
    waitpid(_pid, &status, WNOHANG);
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    else
        return 0;
}