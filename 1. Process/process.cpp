#include "process.hpp"

void sig_handler(int signal) {
    exit(0);
}

std::vector<char*> Process::arg_list(const std::string &name, const std::vector <std::string>& args) {
    std::vector<char*> cstyle_args;
    cstyle_args.reserve(args.size());

    cstyle_args.push_back(const_cast<char*>(name.c_str()));
    for (auto &arg : args)
        cstyle_args.push_back(const_cast<char*>(arg.c_str()));
    cstyle_args.push_back(nullptr);
    
    return cstyle_args;
}

std::string Process::exec_name(const std::string& full_path) {
    std::size_t pos = full_path.rfind('/');
    if (pos == std::string::npos)
        return full_path;
    return full_path.substr(pos);
}

Process::Process(const std::string& path, const std::vector <std::string>& args) {
    pipe2(fd1, 0);
    pipe2(fd2, 0);

    int verif_fd[2];
    pipe2(verif_fd, O_CLOEXEC);

#ifdef DEBUG
    std::cerr << path.c_str() << " " << Process::exec_name(path).c_str() << std::endl;
#endif 
    _pid = fork();
    if (!_pid) {
        dup2(fd1[0], 0);
        dup2(fd2[1], 1);

        ::close(fd1[0]);
        ::close(fd1[1]);
        ::close(fd2[0]);
        ::close(fd2[1]);

        signal(SIGINT, sig_handler);
        execvp(path.c_str(), arg_list(Process::exec_name(path), args).data());
        return;
    }
    ::close(verif_fd[1]);

    char tmp;
    ssize_t size = ::read(verif_fd[0], &tmp, sizeof(tmp));

    int status;
    pid_t pid_result = waitpid(_pid, &status, WNOHANG);
#ifdef DEBUG
    std::cerr << "PID: " << pid_result << std::endl;
    std::cerr << "Status: " << status << std::endl;
#endif
    _noexec = (pid_result != 0);
    ::close(verif_fd[0]);
}

Process::~Process() {
    if (_pid) {
        int status;
        ::close(fd1[0]);
        ::close(fd2[1]);
        ::close(fd1[1]);
        ::close(fd2[0]);
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
    if (!_pid)
        ::close(0);
    else {
#ifdef DEBUG
        std::cerr << "Trying to close Stdin from parent" << std::endl;
#endif
        close();
        waitpid(_pid, NULL, 0);
        exit(1);
    }
}

size_t Process::read(void* data, size_t len) {
    size_t ret_val = ::read(fd2[0], data, len);

#ifdef DEBUG
    if (!ret_val)
        std::cerr << "Trying to read from a closed pipe" << std::endl;
    else
        std::cerr << "Read " << ret_val << " bytes" << std::endl;
#endif

    return ret_val;
}

void Process::readExact(void* data, size_t len) {
    size_t offset = 0;
    while (offset < len) {
        size_t bytes_read = read(data + offset, len);
#ifdef DEBUG
        std::cerr << "Bytes read: " << bytes_read << std::endl;
#endif
        offset += bytes_read;
    }
}

size_t Process::write(const void* data, size_t len) {
    size_t ret_val = ::write(fd1[1], data, len);

#ifdef DEBUG
    std::cerr << "Wrote " << ret_val << " bytes" << std::endl;
#endif

    return ret_val;
}

void Process::writeExact(const void* data, size_t len) {
    size_t offset = 0;
    while (offset < len) {
        size_t bytes_written = write(data + offset, len);
#ifdef DEBUG
        std::cerr << "Bytes written: " << bytes_written << std::endl;
#endif
        offset += bytes_written;
    }
}

bool Process::exec_failed() const {
    return _noexec;
}

int Process::return_status() const {
    if (!_noexec) {
        int status;
        waitpid(_pid, &status, WNOHANG);
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
        else
            return 0;
        
    }
    return -1;
}