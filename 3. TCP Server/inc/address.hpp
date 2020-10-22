#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>
#include <sys/types.h>
#include <memory>

namespace tcp {
    class Address
    {
    private:
        std::string _str_addr;
        int _address;
        int _port;
        struct sockaddr_in _addr {};
    public:
        Address(const std::string &s_addr, int port) noexcept;
        Address(Address &other) noexcept;
        struct sockaddr_in *get_struct() noexcept;
        ~Address() noexcept;
    };
        
}

#endif