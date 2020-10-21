#ifndef SOCKET_H
#define SOCKET_H

#include "descriptor.hpp"

namespace tcp {
    class Socket {
        Descriptor _fd;
    public:
        Socket();
        int get_fd() const;
    };
};

#endif