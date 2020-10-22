#include "descriptor.hpp"

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
        return _fd;
    }
    void Descriptor::close() {
        if (is_open())
            throw ;

        ::close(_fd);
        _fd = -1;
    }
};