#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

namespace tcp {
    class Descriptor {
        int _fd;
        Descriptor(Descriptor &) = delete;
    public:
        Descriptor(int fd = -1) noexcept;
        Descriptor(Descriptor &&) noexcept;
        void set_fd(int fd) noexcept;
        int get_fd() const;
        bool is_open() const;
        void close();
    };
};

#endif