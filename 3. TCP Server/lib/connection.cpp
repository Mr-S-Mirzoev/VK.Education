#include "connection.hpp"
#include <arpa/inet.h>

namespace tcp {

    Connection::Connection(): _addr("127.0.0.1", 8888) {}

    Connection::Connection(Address &&addr): _addr(addr) {}

    Connection::Connection(Connection &&con): _addr(con._addr) {}
    Connection& Connection::operator=(Connection &&con) {
        _addr = con._addr;
        _d = std::move(con._d);
    }
    void Connection::connect(Address addr) {

    }
    void Connection::close();
    size_t Connection::read(char *, size_t);
    size_t Connection::write(const char *, size_t);
    void Connection::readExact(char *, size_t);
    void Connection::writeExact(const char *, size_t);
    void Connection::set_timeout(size_t ms);
};