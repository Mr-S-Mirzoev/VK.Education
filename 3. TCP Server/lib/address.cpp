#include "address.hpp"
#include "exceptions.hpp"

namespace tcp {
    Address::Address(const std::string &s_addr, int port):
        _str_addr(s_addr), _port(port) {}
    Address::Address(const ::sockaddr_in *struct_addr) noexcept:
        _str_addr(::inet_ntoa(struct_addr->sin_addr)), 
        _port(struct_addr->sin_port) {}

    Address::~Address() = default;

    bool Address::operator< (const Address &other) const noexcept {
        return (this->_str_addr < other._str_addr);
    }

    std::string Address::to_string() const {
        return _str_addr + ":" + std::to_string(_port);
    }
    ::sockaddr_in Address::get_struct() const {
        ::sockaddr_in addr {};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(_port);
        if (::inet_aton(_str_addr.c_str(), &addr.sin_addr))
            return addr;
        else
            throw ConnectionFailed(to_string());   
    }
}