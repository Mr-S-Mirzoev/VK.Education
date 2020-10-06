#include "process.hpp"

Process::Process(const std::string& path) {
    int pipe1_fd[2];
    int pipe2_fd[2];
    int verif_fd[2];
    pipe2(verif_fd, O_CLOEXEC);

#ifdef DEBUG
    std::cerr << path.c_str() << " " << Process::exec_name(path).c_str() << std::endl;
#endif 
    _pid = fork();
    if (!_pid) {
        signal(SIGINT, sig_handler);
        execlp(path.c_str(), Process::exec_name(path).c_str(), nullptr);
        return;
    }
    ::close(verif_fd[1]);

    char tmp;
    ssize_t size = ::read(verif_fd[0], &tmp, sizeof(tmp));

    int status;
#ifdef DEBUG
    std::cerr << "PID: " << waitpid(_pid, &status, WNOHANG) << std::endl;
    std::cerr << "Status: " << status << std::endl;
#endif
}

Process::~Process() {
    if (_pid) {
        int status;
        waitpid(_pid, &status, 0);
#ifdef DEBUG
        std::cerr << WEXITSTATUS(status) << std::endl;
#endif
    }
}

void Process::close() {
    if (_pid)
        kill(_pid, SIGINT);
    else {
#ifdef DEBUG
        std::cerr << "Trying to kill softly from child" << std::endl;
#endif
        exit(1);
    }
}

void Process::closeStdin() {

}

size_t Process::read(void* data, size_t len) {
    return 0;
}

void Process::readExact(void* data, size_t len) {

}

size_t Process::write(const void* data, size_t len) {
    return 0;
}

void Process::writeExact(const void* data, size_t len) {

}