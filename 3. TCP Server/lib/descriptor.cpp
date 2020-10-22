#include "descriptor.hpp"

#include "exceptions.hpp"

#include <unistd.h>

namespace tcp {
    Descriptor::Descriptor(int fd = -1): _fd(fd) {}
    Descriptor::Descriptor(Descriptor &&other): _fd(other._fd) {
        other._fd = -1;
    }
    void Descriptor::set_fd(int fd) {
        _fd = fd;
    }
    int Descriptor::get_fd() const {
        if (broken())
            throw BadDescriptorUsed();
        return _fd;
    }

    bool Descriptor::broken() const noexcept {
        return (_fd < 0);
    }

    void Descriptor::close() {
        if (broken())
            throw BadDescriptorUsed();

        ::close(_fd);
        _fd = -1;
    }
};