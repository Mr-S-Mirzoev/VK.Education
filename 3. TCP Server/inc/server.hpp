#ifndef SERVER_H
#define SERVER_H

#include "descriptor.hpp"
#include <string>
#include "connection.hpp"

namespace tcp {
    /* Maximum queue length specifiable by listen.  */
    constexpr unsigned MAX_POSSIBLE_CONNECTIONS = 100;

    class Server {
        Descriptor _listen_socket;
        uint16_t _port;
        unsigned _max_con;
        void bind();
        void listen ();
    public:
        Server(Server &&);
        Server(int port, unsigned max_con = MAX_POSSIBLE_CONNECTIONS);

        Server& operator= (Server &&);

        Connection accept();
        void close();

        void set_max_connection(unsigned max_connection) noexcept;
        void set_timeout(size_t ms);
    };
} // namespace tcp

#endif