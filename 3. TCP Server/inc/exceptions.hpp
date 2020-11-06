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

    class SocketClosedRead: public std::runtime_error {
    public:
        explicit SocketClosedRead();
    };

    class SocketClosedWrite: public std::runtime_error {
    public:
        explicit SocketClosedWrite();
    };

    class SocketClosedListen: public std::runtime_error {
    public:
        explicit SocketClosedListen();
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