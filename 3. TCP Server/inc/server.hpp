#ifndef SERVER_H
#define SERVER_H

#include "socket.hpp"
#include <string>
#include "connection.hpp"
#include <map>

namespace tcp {
    class Server {
        Socket _listen_socket;
        int _port;
        unsigned _max_con;
        void bind();
        void listen ();
    public:
        Server(Server &&);
        Server(int port, unsigned max_con = SOMAXCONN);

        Server& operator= (Server &&);

        Connection accept();
        void close();

        void set_max_connection(unsigned max_connection=SOMAXCONN) noexcept;
        void set_timeout(size_t ms);
    };
};

#endif