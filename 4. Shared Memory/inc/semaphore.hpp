#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <semaphore.h>
#include "allocator.hpp"
#include "mmap_wrapper.hpp"

namespace shmem {

    class Semaphore {
        MMapWrapper <::sem_t> _value;
    public:
        Semaphore();
        ~Semaphore();
        void unlock();
        void lock();
    };
    
}

#endif // SEMAPHORE_H