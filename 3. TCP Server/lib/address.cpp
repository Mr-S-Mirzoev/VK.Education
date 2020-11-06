#include "address.hpp"
#include "exceptions.hpp"

namespace tcp {
    Address::Address(const std::string &s_addr, int port):
        _port(port) {
        in_addr_t tmp = ::inet_network(s_addr.c_str());

        if (tmp == -1)
            throw AddressNotConverted{};
        
        _address = tmp;
    }
    Address::Address(const ::sockaddr_in &struct_addr) noexcept:
        _address(struct_addr.sin_addr.s_addr),
        _port(struct_addr.sin_port) {}

    std::string Address::to_string() const {
        ::in_addr address_handle {0};
        address_handle.s_addr = _address;

        std::string ipv4 = ::inet_ntoa(address_handle);

        return ipv4 + ":" + std::to_string(_port);
    }
    ::sockaddr_in Address::get_struct() const noexcept {
        ::sockaddr_in addr {};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(_port);
        addr.sin_addr.s_addr = _address;
        return addr;
    }

    Address any_address(int port) {
        ::sockaddr_in remote = {0};
        /* Internet address family */
        remote.sin_family = AF_INET;
        /* Any incoming interface */
        remote.sin_addr.s_addr = htonl(INADDR_ANY);
        remote.sin_port = htons(port);
        return Address(remote);
    }
} // namespace tcp