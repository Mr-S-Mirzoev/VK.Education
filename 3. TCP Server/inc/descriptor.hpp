#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

namespace tcp {
    class Descriptor {
        int _fd;
    public:
        Descriptor();
        Descriptor(int fd);
        Descriptor(Descriptor &&);
        void set_fd(int fd);
        int get_fd();
        void close();
    };
};

#endif