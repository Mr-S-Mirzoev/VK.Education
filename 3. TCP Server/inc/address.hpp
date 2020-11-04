#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>
#include <sys/types.h>
#include <memory>
#include <arpa/inet.h>

namespace tcp {
    class Address
    {
    private:
        std::string _str_addr;
        int _address;
        int _port;
        struct sockaddr_in _addr {};
    public:
        Address() noexcept;
        Address(const std::string &s_addr, int port) noexcept;
        Address(const Address &other) noexcept;
        Address(const struct sockaddr_in *struct_addr) noexcept;

        ~Address() noexcept;

        bool operator< (const Address &other) const noexcept;

        std::string to_string() const;
        struct sockaddr_in get_struct() const;
    };
        
}

#endif