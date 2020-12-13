#ifndef EPOLL_H
#define EPOLL_H

#include "descriptor.hpp"
#include <ctype.h>

namespace net {
    class Epoll
    {
    private:
        tcp::Descriptor _epoll_fd;
    public:
        Epoll(/* args */);
        ~Epoll();

        void mod (tcp::Descriptor);
        void add ();
        void del ();
        void wait (size_t timeout_ms);
    };
    
    Epoll::Epoll(/* args */)
    {
    }
    
    Epoll::~Epoll()
    {
    }
    
} // net

#endif // EPOLL_H