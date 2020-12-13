#ifndef BUFF_CONN_H
#define BUFF_CONN_H

#include <string>
#include "connection.hpp"

namespace net {
    class BufferedConnection {
        std::string _read_buf;
        std::string _write_buf;
        tcp::Connection &connection;
    public:
        BufferedConnection(Service);
        void subscribe();
        void unsubscribe();
        std::string get_read_buf();
        std::string get_write_buf();
        void close();        
    }
} // net

#endif // BUFF_CONN_H