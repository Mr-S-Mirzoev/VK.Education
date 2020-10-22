#include "pipe2.hpp"
#include <fcntl.h>
#include <unistd.h>

int pipe2(int pipefd[2], int flags) {
    int ret_val = pipe(pipefd);
    if (ret_val < 0)
        return ret_val;
    if (flags == O_CLOEXEC) {
        if (fcntl(pipefd[0], F_SETFD, FD_CLOEXEC) == -1)
            return -1;
        if (fcntl(pipefd[1], F_SETFD, FD_CLOEXEC) == -1)
            return -1;
    }
    return ret_val;
}