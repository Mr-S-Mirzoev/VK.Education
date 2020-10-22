#ifndef CONNECTION_H
#define CONNECTION_H

#include "descriptor.hpp"
#include "address.hpp"
#include <cstddef>
#include <string>

namespace tcp {
    class Connection {
        Address _addr; // address to which we are connecting
        Descriptor _d; // RAII class holding socket descriptor
        bool _is_set;  // if not connected restrict operations until "connect" is called

        /* 
            We define copy constructor and assignment operator as deleted functions
            as from the reason behind this class there cannot be two different connections
            to the same address.
        */
        Connection(const Connection &rhs) = delete;
        Connection &operator=(const Connection &rhs) = delete;
    public:
        Connection();
        Connection(Address &address);
        Connection(Connection &&);

        Connection& operator=(Connection &&) noexcept; // move operator

        void connect(Address address);
        void close();

        size_t read(char *, size_t);
        size_t write(const char *, size_t);
        void readExact(char *, size_t);
        void writeExact(const char *, size_t);

        void set_timeout(size_t ms);
        bool is_open() const noexcept;
    };
};


#endif