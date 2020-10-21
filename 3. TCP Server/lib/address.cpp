#include "address.hpp"
#include <arpa/inet.h>

namespace tcp {
    Address::Address() = default;

    Address::Address(const std::string &s_addr, int port):
        _str_addr(s_addr), _port(port), _addr(new sockaddr_in) {
        _addr->sin_family = AF_INET;
        _addr->sin_port = htons(_port);
        ::inet_aton(s_addr.c_str(), &_addr->sin_addr);
    }
    
    struct sockaddr_in *Address::get_struct() {
        return _addr.get();
    }

    Address::~Address() = default;
}