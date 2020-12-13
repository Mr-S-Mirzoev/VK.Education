#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

namespace tcp {
    std::string last_error();

    class BadDescriptorUsed: public std::runtime_error {
    public:
        BadDescriptorUsed();
    };

    class SocketNotCreated: public std::runtime_error {
    public:
        SocketNotCreated(const std::string&);
    };

    class AddressNotBuilt: public std::runtime_error {
    public:
        AddressNotBuilt(const std::string&);
    };

    class AddressBadPort: public AddressNotBuilt {
    public:
        AddressBadPort();
    };

    class AddressNotConverted: public AddressNotBuilt {
    public:
        AddressNotConverted();
    };
    
    class ConnectionFailed: public std::runtime_error {
    public:
        explicit ConnectionFailed(const std::string&);
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

    class ServerError: public std::runtime_error {
    public:
        ServerError(std::string s = "");
    };

    class ServerListenError: public ServerError {
    public:
        ServerListenError();
    };

    class ServerBindError: public ServerError {
    public:
        ServerBindError(int port);
    };

    class ServerAcceptError: public ServerError {
    public:
        ServerAcceptError();
    };

    class ServerTimeOutNotSet: public ServerError {
    public:
        ServerTimeOutNotSet();
    };

    class ClientTimeOutNotSetRead: public std::runtime_error {
    public:
        ClientTimeOutNotSetRead();
    };

    class ClientTimeOutNotSetWrite: public std::runtime_error {
    public:
        ClientTimeOutNotSetWrite();
    };
} // namespace tcp

#endif