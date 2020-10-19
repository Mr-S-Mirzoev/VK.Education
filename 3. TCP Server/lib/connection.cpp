#include "connection.hpp"
#include <arpa/inet.h>

namespace tcp {

    Connection::Connection() = default;

    Connection::Connection(std::string address, unsigned port) {
        sockaddr_in addr{}; // no memset
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        ::inet_aton(address.c_str(), &addr.sin_addr);
    }

    Connection::Connection(Connection &&con) = default;
    Connection& Connection::operator=(Connection &&con) {
        
    }
    void Connection::connect(std::string addr, unsigned port) {

    }
    void Connection::close();
    size_t Connection::read(char *, size_t);
    size_t Connection::write(const char *, size_t);
    void Connection::readExact(char *, size_t);
    void Connection::writeExact(const char *, size_t);
    void Connection::set_timeout(size_t ms);
};