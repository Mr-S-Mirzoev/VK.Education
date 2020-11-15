#ifndef MMAP_WRAPPER_H
#define MMAP_WRAPPER_H

#include <cstddef>
#include "exceptions.hpp"

namespace shmem
{
    template <typename T>
    class MMapWrapper
    {
    private:
        ::size_t _length;
        void *_addr;
    public:
        MMapWrapper(::size_t bytes_count) {
            if (::mmap( nullptr, 
                        bytes_count, 
                        PROT_READ | PROT_WRITE, 
                        MAP_SHARED | MAP_ANONYMOUS, 
                        -1, 
                        0) == MAP_FAILED)
                throw MMapInitError(errno);
        }
        ~MMapWrapper() {
            if (::munmap(_addr, _length) == -1)
            throw MMapDeInitError(errno);
        }

        T *get_addr() const {
            return static_cast<T *>(_addr);
        }
    };
    
} // namespace shmem


#endif // MMAP_WRAPPER_H