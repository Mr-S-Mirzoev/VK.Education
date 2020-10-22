#include "address.hpp"
#include <arpa/inet.h>

namespace tcp {
    Address::Address(const std::string &s_addr, int port):
        _str_addr(s_addr), _port(port), _addr() {
        _addr.sin_family = AF_INET;
        _addr.sin_port = htons(_port);
        ::inet_aton(s_addr.c_str(), &_addr.sin_addr);
    }

    std::string Address::to_string() const {
        return _str_addr + ":" + std::to_string(_port);
    }
    
    struct sockaddr_in Address::get_struct() const {
        return _addr;
    }
}