#ifndef SOCKET_H
#define SOCKET_H

#include "descriptor.hpp"

namespace tcp {
    class Socket {
        Descriptor _fd;
    public:
        Socket();
        Socket(Socket &&);

        Socket& operator= (Socket &&);

        int get_fd() const;
        operator bool() const noexcept;

        void close();

        ~Socket();
    };
};

#endif