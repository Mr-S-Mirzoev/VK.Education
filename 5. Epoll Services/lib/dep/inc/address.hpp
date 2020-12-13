#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>
#include <arpa/inet.h>

namespace tcp {
    class Address
    {
    private:
        in_addr_t _address;
        uint16_t _port;
    public:
        Address() = default; // To makeit possible to use address uninitialized.
        Address(const std::string &s_addr, int port);
        Address(const Address &other) = default;
        Address(const ::sockaddr_in &struct_addr) noexcept;

        ~Address() = default;

        std::string to_string() const;
        struct sockaddr_in get_struct() const noexcept;
    };

    Address any_address(int port);
} // namespace tcp

#endif