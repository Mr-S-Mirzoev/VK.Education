#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

namespace tcp {
    class BadDescriptorUsed: std::runtime_error {
    public:
        BadDescriptorUsed(std::string s = "Trying to use broken or closed decriptor");
    };
    
    class ConnectionFailed: std::runtime_error {
    public:
        explicit ConnectionFailed(std::string addr, 
            std::string s = "Connection failed. Address: ");
    };
};

#endif