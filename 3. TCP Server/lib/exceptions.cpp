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
}