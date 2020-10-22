#include "connection.hpp"
#include <arpa/inet.h>
#include "exceptions.hpp"

namespace tcp {

    Connection::Connection(): _addr("127.0.0.1", 8888) {}

    Connection::Connection(Address &&addr): _addr(addr) {}

    Connection::Connection(Connection &&con): _addr(con._addr) {}
    Connection& Connection::operator=(Connection &&con) {
        _addr = con._addr;
        _d = std::move(con._d);
    }
  
    void Connection::connect(Address addr) {
        int ret_val = ::connect(_d.get_fd(), 
            reinterpret_cast<sockaddr*> (&addr.get_struct()), 
            sizeof(addr.get_struct()));

        if (ret_val != 0)
            throw ConnectionFailed(addr.to_string());
    }
    void Connection::close() {
        if (!is_open) 
            throw BadDescriptorUsed();
        
        _d.close();
    }

    size_t Connection::read(char *buffer, size_t buf_len) {
        
    }
    size_t Connection::write(const char *data, size_t buf_len);
    void Connection::readExact(char *buffer, size_t buf_len);
    void Connection::writeExact(const char *data, size_t buf_len);

    void Connection::set_timeout(size_t ms);
    bool Connection::is_open() const noexcept {
        return (!_d.broken())
    }
};