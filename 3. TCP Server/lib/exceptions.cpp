#include "exceptions.hpp"

namespace tcp {
    BadDescriptorUsed::BadDescriptorUsed
        (std::string s): std::runtime_error(s) {}

    ConnectionFailed::ConnectionFailed 
        (std::string addr, std::string s = "Connection failed. Address: "): std::runtime_error(s + addr) {}

}