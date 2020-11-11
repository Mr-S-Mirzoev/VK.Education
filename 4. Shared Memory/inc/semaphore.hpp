#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <semaphore.h>

namespace shmem {
    class Semaphore {
        ::sem_t _value;
    public:
        Semaphore();
        void post();
        void wait();
        void destroy();
    };
}

#endif // SEMAPHORE_H