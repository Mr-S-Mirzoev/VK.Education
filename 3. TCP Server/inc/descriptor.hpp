#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

namespace tcp {
    class Descriptor {
        int _fd;
    public:
        Descriptor(Descriptor &&) = default;
        Descriptor(int fd = -1);

        void set_fd(int fd) noexcept;
        int get_fd() const;

        bool broken() const noexcept;

        void close();
    };
};

#endif