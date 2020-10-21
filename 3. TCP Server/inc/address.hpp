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
        std::shared_ptr<struct sockaddr_in> _addr;
    public:
        Address();
        Address(const std::string &addr, int port);
        struct sockaddr_in *get_struct();
        ~Address();
    };
        
}

#endif