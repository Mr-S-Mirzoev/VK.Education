#include "exceptions.hpp"

namespace tcp {
    BadDescriptorUsed::BadDescriptorUsed (): 
        std::runtime_error("Trying to use broken or closed decriptor") {}

    ConnectionFailed::ConnectionFailed (const std::string &addr): 
        std::runtime_error("Connection failed. Address: " + addr) {}

    SocketClosed::SocketClosed(std::string s = "read"):
        std::runtime_error("Socket is closed. Failed to " + s) {}

    ReadFailed::ReadFailed():
        std::runtime_error("Reading failed.") {}

    WriteFailed::WriteFailed():
        std::runtime_error("Writing failed.") {}
}