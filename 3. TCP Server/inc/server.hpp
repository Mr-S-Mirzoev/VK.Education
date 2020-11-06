#ifndef SERVER_H
#define SERVER_H

#include "descriptor.hpp"
#include <string>
#include "connection.hpp"

namespace tcp {
    const unsigned default_max_connection_count = 100;

    class Server {
        Descriptor _listen_socket;
        int _port;
        unsigned _max_con;
        void bind();
        void listen ();
    public:
        Server(Server &&);
        Server(int port, unsigned max_con = default_max_connection_count);

        Server& operator= (Server &&);

        Connection accept();
        void close();

        void set_max_connection(unsigned max_connection) noexcept;
        void set_timeout(size_t ms);
    };
} // namespace tcp

#endif