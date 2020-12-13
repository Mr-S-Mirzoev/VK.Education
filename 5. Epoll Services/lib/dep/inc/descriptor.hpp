#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

namespace tcp {
    class Descriptor {
        int _fd;
        Descriptor(const Descriptor &) = delete;
        bool broken () const noexcept;
    public:
        Descriptor(Descriptor &&);
        Descriptor(int fd = -1);
        ~Descriptor();

        Descriptor& operator= (Descriptor &&);

        void set_fd(int fd);
        int get_fd() const;

        operator bool() const noexcept;
      
        void close();
    };

    Descriptor create_inet4_socket();
} // namespace tcp

#endif