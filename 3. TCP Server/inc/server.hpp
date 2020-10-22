#ifndef SERVER_H
#define SERVER_H

#include "descriptor.hpp"
#include <string>
#include "connection.hpp"
#include <map>

#ifndef SOMAXCONN
#define SOMAXCONN 2
#endif

namespace tcp {
    class Server {
        Descriptor _d;
        size_t _timeout;
        bool _is_open;
        bool _is_set;
        Address _addr;
        std::map <Address, Descriptor> _clients;
        unsigned _max_con;
    public:
        Server();
        Server(Server &&);
        Server(std::string address, unsigned port, unsigned max_connection=SOMAXCONN);

        Server& operator= (Server &&);

        void open(std::string address, unsigned port, unsigned max_connection=SOMAXCONN);
        Connection accept();
        void close();

        void set_max_connection(unsigned max_connection=SOMAXCONN) noexcept;
        void set_timeout(size_t ms);
    };
};

#endif