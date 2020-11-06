#ifndef CONNECTION_H
#define CONNECTION_H

#include "descriptor.hpp"
#include "address.hpp"
#include <string>

namespace tcp {
    class Connection {
        Address _addr; // address to which we are connecting
        Descriptor _sock; // RAII class holding socket descriptor

        /* 
            We define copy constructor and assignment operator as deleted functions
            as from the reason behind this class there cannot be two different connections
            through the same socket.
        */
        Connection(const Connection &rhs) = delete;
        Connection &operator=(const Connection &rhs) = delete;
    public:
        Connection(const Address &addr);
        Connection(const Address &addr, Descriptor &&d);
        Connection(Connection &&);

        Connection& operator=(Connection &&) noexcept; // move operator

        void connect(const Address &address);
        void close();

        size_t read(char *, size_t);
        size_t write(const char *, size_t);
        void readExact(char *, size_t);
        void writeExact(const char *, size_t);

        void set_timeout(size_t ms);
        bool is_open() const noexcept;
    };
} // namespace tcp

#endif