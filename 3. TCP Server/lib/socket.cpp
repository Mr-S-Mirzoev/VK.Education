#include "socket.hpp"
#include <arpa/inet.h>

#include <iostream>

namespace tcp {
    Socket::Socket() {
        int fd = ::socket(PF_INET, SOCK_STREAM, 0);
        if (fd == -1)
            std::cerr << "Socket creation failed" << std::endl;
        _fd.set_fd(fd);
    }

    int Socket::get_fd() const {
        return _fd.get_fd();
    }
};