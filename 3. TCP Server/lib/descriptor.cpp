#include "descriptor.hpp"
#include "exceptions.hpp"

#include <unistd.h>
#include <utility>
#include <arpa/inet.h>
#include <iostream>

namespace tcp {
    Descriptor::Descriptor(int fd) {
        if (fd < 0)
            throw tcp::BadDescriptorUsed{};
        
        _fd = fd;
    }
    Descriptor::Descriptor(Descriptor &&other) {
        _fd = std::exchange(other._fd, -1);
    }
    Descriptor::~Descriptor () {
        if (!broken())
            close();
    }

    // Setter and getter
    void Descriptor::set_fd(int fd) {
        if (!broken())
            close();
        _fd = fd;
    }
    int Descriptor::get_fd() const {
        if (broken())
            throw BadDescriptorUsed();
        
        return _fd;
    }

    Descriptor& Descriptor::operator= (Descriptor &&other) {
        if (!broken())
            close();
        _fd = std::exchange(other._fd, -1);

        return *this;
    }

    bool Descriptor::broken() const noexcept {
        return _fd < 0;
    }

    Descriptor::operator bool() const noexcept {
        return !broken();
    }

    void Descriptor::close() {
        if (broken())
            throw BadDescriptorUsed();

        ::close(_fd);
        _fd = -1;
    }

    Descriptor create_inet4_socket() {
        int sock_no = ::socket(PF_INET, SOCK_STREAM, 0);
        if (sock_no == -1) {
            throw SocketNotCreated(last_error());
        }
        return std::move(Descriptor(sock_no));
    }
} // namespace tcp