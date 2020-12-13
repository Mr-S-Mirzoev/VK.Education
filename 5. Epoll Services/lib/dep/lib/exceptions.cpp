#include "exceptions.hpp"
#include <cerrno>
#include <cstring>

namespace tcp {
    std::string last_error() {
        return strerror(errno);
    }

    BadDescriptorUsed::BadDescriptorUsed (): 
        std::runtime_error("Trying to use broken or closed decriptor") {}

    SocketNotCreated::SocketNotCreated (const std::string& error_string):
        std::runtime_error("Socket not created due to: " + error_string) {}

    AddressNotBuilt::AddressNotBuilt(const std::string &s):
        std::runtime_error(s) {}

    AddressNotConverted::AddressNotConverted():
        AddressNotBuilt("Address not built due to ") {}

    ConnectionFailed::ConnectionFailed (const std::string &addr): 
        std::runtime_error("Connection failed. Address: " + addr) {}

    SocketClosedRead::SocketClosedRead():
        std::runtime_error("Socket is closed. Failed to read.") {}

    SocketClosedWrite::SocketClosedWrite():
        std::runtime_error("Socket is closed. Failed to write.") {}

    SocketClosedListen::SocketClosedListen():
        std::runtime_error("Socket is closed. Failed to listen.") {}

    ReadFailed::ReadFailed():
        std::runtime_error("Reading failed.") {}

    WriteFailed::WriteFailed():
        std::runtime_error("Writing failed.") {}

    ServerError::ServerError(std::string s):
        std::runtime_error(s) {}

    ServerListenError::ServerListenError():
        ServerError("Failed to start server (doen't listen)") {}

    ServerBindError::ServerBindError(int port):
        ServerError("Failed to start server at port: " + std::to_string(port)) {}

    ServerAcceptError::ServerAcceptError():
        ServerError("Failed to accept client.") {}

    ServerTimeOutNotSet::ServerTimeOutNotSet():
        ServerError("Failed to set receive timeout for server.") {}

    ClientTimeOutNotSetRead::ClientTimeOutNotSetRead():
        std::runtime_error("Failed to set receive timeout for client.") {}

    ClientTimeOutNotSetWrite::ClientTimeOutNotSetWrite():
        std::runtime_error("Failed to set send timeout for client.") {}
} // namespace tcp