#include "exceptions.hpp"

namespace tcp {
    BadDescriptorUsed::BadDescriptorUsed (): 
        std::runtime_error("Trying to use broken or closed decriptor") {}

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
}