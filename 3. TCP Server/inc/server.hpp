#ifndef SERVER_H
#define SERVER_H

#include "descriptor.hpp"
#include <string>

#ifndef SOMAXCONN
#define SOMAXCONN 2
#endif

namespace tcp {
    class Server {
        Descriptor _d;
    public:
        Server();
        Server(Server &&);
        Server(std::string address, unsigned port, unsigned max_connection=SOMAXCONN);
        void open(std::string address, unsigned port, unsigned max_connection=SOMAXCONN);
        Server& operator= (Server &&);
        Connection accept();
        void close();
        void set_max_connection();
        void set_timeout(size_t ms);
    };
};

#endif