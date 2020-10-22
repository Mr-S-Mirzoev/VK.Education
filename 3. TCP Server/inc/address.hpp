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
        Address() = default;
        ~Address() = default;

        Address(const std::string &addr, int port);
        
        std::string Address::to_string() const;
        struct sockaddr_in get_struct() const;
    };
        
}

#endif