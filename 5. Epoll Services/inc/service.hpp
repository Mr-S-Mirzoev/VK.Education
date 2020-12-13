#ifndef SERVICE_H
#define SERVICE_H

#include "server.hpp"

namespace net {
    class Service
    {
    private:
        IServiceListener _listener;
        // _connections;
        tcp::Server _server;
        Epoll _epoll;
    public:
        Service(/* args */);
        ~Service();
    };
    
    Service::Service(/* args */)
    {
    }
    
    Service::~Service()
    {
    }
    
} // net

#endif // SERVICE_H