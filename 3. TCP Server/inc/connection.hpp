#ifndef CONNECTION_H
#define CONNECTION_H

#include "descriptor.hpp"
#include <cstddef>
#include <string>

namespace tcp {
    class Connection {
        Descriptor _d;
    public:
        Connection();
        Connection(std::string address, unsigned port);
        Connection(Connection &&);
        Connection& operator=(Connection &&);
        void connect(std::string addr, unsigned port);
        void close();
        size_t read(char *, size_t);
        size_t write(const char *, size_t);
        void readExact(char *, size_t);
        void writeExact(const char *, size_t);
        void set_timeout(size_t ms);
    };
};


#endif