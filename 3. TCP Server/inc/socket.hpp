#ifndef SOCKET_H
#define SOCKET_H

namespace tcp {
    class Socket {
        int _fd;
    public:
        Socket();
        int get_fd() const;
    };
};

#endif