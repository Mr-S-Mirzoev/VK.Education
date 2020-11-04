#ifndef SERVER_H
#define SERVER_H

#include "descriptor.hpp"
#include <string>
#include "connection.hpp"
#include <map>

namespace tcp {
    class Server {
        Descriptor _d;
        Address _addr;
        unsigned _max_con;
        void listen (const int);
    public:
        Server(Server &&);
        Server(std::string address, unsigned port, unsigned max_con = SOMAXCONN);

        Server& operator= (Server &&);

        void open();
        bool is_open() const noexcept;
        Connection accept();
        void close();

        void set_max_connection(unsigned max_connection=SOMAXCONN) noexcept;
        void set_timeout(size_t ms);
    };
};

#endif