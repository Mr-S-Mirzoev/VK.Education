#include "socket.hpp"
#include <arpa/inet.h>

namespace tcp {
    Socket::Socket() {
        _fd = ::socket(PF_INET, SOCK_STREAM, 0);
    }

    int Socket::get_fd() const {
        return _fd;
    }
};