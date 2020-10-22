#ifndef CONNECTION_H
#define CONNECTION_H

#include "descriptor.hpp"
#include "address.hpp"
#include <cstddef>
#include <string>

namespace tcp {
    class Connection {
        Descriptor _d;
        Address _addr;
        Connection(const Connection &rhs) = delete;
        Connection &operator=(const Connection &rhs) = delete;
    public:
        Connection();
        Connection(Connection &&);

        Connection& operator=(Connection &&) noexcept;

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