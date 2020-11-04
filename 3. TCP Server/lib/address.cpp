#include "address.hpp"

namespace tcp {
    Address::Address(const std::string &s_addr, int port):
        _str_addr(s_addr), _port(port) {
        _addr.sin_family = AF_INET;
        _addr.sin_port = htons(_port);
        ::inet_aton(s_addr.c_str(), &_addr.sin_addr);
    }
    Address::Address() noexcept: Address("127.0.0.1", 8888) {}
    Address::Address(const Address &other) noexcept: 
        _addr({other._addr}), _str_addr(other._str_addr), 
        _port(other._port) {}
    Address::Address(const struct sockaddr_in *struct_addr) noexcept:
        _str_addr(::inet_ntoa(struct_addr->sin_addr)), 
        _port(struct_addr->sin_port) {
        _addr = *struct_addr;
    }

    Address::~Address() = default;

    bool Address::operator< (const Address &other) const noexcept {
        return (this->_str_addr < other._str_addr);
    }

    std::string Address::to_string() const {
        return _str_addr + ":" + std::to_string(_port);
    }
    struct sockaddr_in Address::get_struct() const {
        return _addr;
    }
}