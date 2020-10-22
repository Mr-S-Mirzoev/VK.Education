#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

namespace tcp {
    class BadDescriptorUsed: public std::runtime_error {
    public:
        BadDescriptorUsed();
    };
    
    class ConnectionFailed: public std::runtime_error {
    public:
        explicit ConnectionFailed(const std::string &addr);
    };

    class SocketClosed: public std::runtime_error {
    public:
        explicit SocketClosed(std::string s = "read");
    };

    class ReadFailed: public std::runtime_error {
    public:
        ReadFailed();
    };

    class WriteFailed: public std::runtime_error {
    public:
        WriteFailed();
    };
};

#endif