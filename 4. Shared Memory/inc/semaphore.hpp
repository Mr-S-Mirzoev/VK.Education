#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <semaphore.h>

namespace shmem {

    class Semaphore {
        ::sem_t _value;
    public:
        Semaphore();
        ~Semaphore();
        void unlock();
        void lock();
    };
    
}

#endif // SEMAPHORE_H