#include "process.hpp"
#include "ostype.hpp"

#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#if PLATFORM_ENUM == OS_OSX
    int pipe2(int pipefd[2], int flags) {
        int ret_val = pipe(pipefd);
        if (flags == O_CLOEXEC) {
            fcntl(pipefd[0], F_SETFD, FD_CLOEXEC);
            fcntl(pipefd[1], F_SETFD, FD_CLOEXEC);
        }
        return ret_val;
    }
#endif

std::vector<char*> arg_list(const std::string &name, const std::vector <std::string>& args) {
    std::vector<char*> cstyle_args;
    cstyle_args.reserve(args.size() + 1);

    cstyle_args.push_back(const_cast<char*>(name.c_str()));
    for (auto &arg : args)
        cstyle_args.push_back(const_cast<char*>(arg.c_str()));
    cstyle_args.push_back(nullptr);
    
    return cstyle_args;
}

std::string exec_name(const std::string& full_path) {
    std::size_t pos = full_path.rfind('/');
    if (pos == std::string::npos)
        return full_path;
    return full_path.substr(pos + 1);
}

inline bool is_child(pid_t pid) {
    return (pid == 0);
}

inline bool POSIX_ERROR(int ret_val) {
    return (ret_val < 0);
}



// Process implementation

Process::Process(const std::string& path, const std::vector <std::string>& args) {
    int fd1[2];
    int fd2[2];

    int ret;

    ret = pipe2(fd1, 0);
    if (ret == -1) {
#ifdef DEBUG
        std::cerr << "Pipe1 initialization failed" << std::endl;
#endif
        return;
    }

    ret = pipe2(fd2, 0);
    if (ret == -1) {
#ifdef DEBUG
        std::cerr << "Pipe2 initialization failed" << std::endl;
#endif
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

#ifdef DEBUG
    std::cerr << path.c_str() << " " << exec_name(path).c_str() << std::endl;
#endif 
    _pid = fork();

    if (is_child(_pid)) {
#ifdef DEBUG
        std::cerr << "Forked off successfully" << std::endl;
#endif

        dup2(fd1[0], STDIN_FILENO);
        dup2(fd2[1], STDOUT_FILENO);

        ::close(fd1[0]);
        ::close(fd1[1]);
        ::close(fd2[0]);
        ::close(fd2[1]);

        execvp(path.c_str(), arg_list(exec_name(path), args).data());

#ifdef DEBUG
        std::cerr << "EXECVP failed" << std::endl;
#endif

        exit(-1);
    } else if (POSIX_ERROR(_pid)) {
        ::close(fd1[0]);
        ::close(fd1[1]);
        ::close(fd2[0]);
        ::close(fd2[1]);
        ::close(verif_fd[0]);
        ::close(verif_fd[1]);

#ifdef DEBUG
        std::cerr << "Forking off failed" << std::endl;
#endif

        return;
    } else {
        ::close(verif_fd[1]);  // Attaching this action to logical part of forking off
    }

    char tmp;
    ssize_t size = ::read(verif_fd[0], &tmp, sizeof(tmp));
    ::close(verif_fd[0]);

    int status;
    pid_t pid_result = waitpid(_pid, &status, WNOHANG);
#ifdef DEBUG
    std::cerr << "PID: " << pid_result << std::endl;
    std::cerr << "Status: " << status << std::endl;
#endif

    _fd_in = fd2[0];
    _fd_out = fd1[1];

    bool _noexec = (pid_result != 0);
    if (_noexec) {
        ::close(_fd_in);
        _fd_in = -1;
        ::close(_fd_out);
        _fd_out = -1;
        kill(_pid, SIGKILL);
        throw(std::runtime_error("Execution of programm " + path + " failed"));
    }

    //::close(fd2[1]);
    //::close(fd1[0]);
}

Process::~Process() {
    if (!is_child(_pid)) {
        int status;

        ::close(_fd_in);
        ::close(_fd_out);

        kill(_pid, SIGKILL);
        waitpid(_pid, &status, 0);
#ifdef DEBUG
        std::cerr << WEXITSTATUS(status) << std::endl;
#endif
    }
}

void Process::close() {
    if (!is_child(_pid)) {
        ::close(_fd_in);
        _fd_in = -1;
        ::close(_fd_out);
        _fd_out = -1;
        kill(_pid, SIGINT);
    } else {
#ifdef DEBUG
        std::cerr << "Trying to kill softly from child" << std::endl;
#endif
        exit(1);
    }
}

void Process::closeStdin() {
#ifdef DEBUG
        std::cerr << "Trying to close Stdin from parent" << std::endl;
#endif
    if (!is_child(_pid))
        ::close(_fd_out);
}

size_t Process::read(void* data, size_t len) {
    if (POSIX_ERROR(fcntl(_fd_in, F_GETFD))) 
        throw std::runtime_error("Reading failed due to the fact file is closed.");

    size_t ret_val = ::read(_fd_in, data, len);

    if (POSIX_ERROR(ret_val))
        throw std::runtime_error("Reading data failed");
#ifdef DEBUG
    else if (!ret_val)
        std::cerr << "Trying to read from a closed pipe" << std::endl;
    else
        std::cerr << "Read " << ret_val << " bytes" << std::endl;
#endif

    return ret_val;
}

void Process::readExact(void* data, size_t len) {
    char *sized_data = static_cast<char *>(data);

    size_t offset = 0;
    while (offset < len) {
        size_t bytes_read = read(sized_data + offset, len);
#ifdef DEBUG
        std::cerr << "Bytes read: " << bytes_read << std::endl;
#endif
        if (bytes_read == 0)
            throw std::runtime_error("Error while reading");
        
        offset += bytes_read;
    }
}

size_t Process::write(const void* data, size_t len) {
    if (POSIX_ERROR(fcntl(_fd_out, F_GETFD))) 
        throw std::runtime_error("Writing failed due to the fact file is closed.");

    size_t ret_val = ::write(_fd_out, data, len);

    if (POSIX_ERROR(ret_val))
        throw std::runtime_error("Writing failed");

#ifdef DEBUG
    std::cerr << "Wrote " << ret_val << " bytes" << std::endl;
#endif

    return ret_val;
}

void Process::writeExact(const void* data, size_t len) {
    size_t offset = 0;
    const char *sized_data = static_cast<const char *>(data);
    while (offset < len) {
        size_t bytes_written = write(sized_data + offset, len);
#ifdef DEBUG
        std::cerr << "Data: " << sized_data << std::endl;
        std::cerr << "Bytes written: " << bytes_written << std::endl;
#endif
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