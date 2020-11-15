#ifndef SEMLOCK_H
#define SEMLOCK_H

#include "semaphore.hpp"

namespace shmem {

    class SemLock {
        Semaphore &_threshold;
    public:
        SemLock(Semaphore &threshold);
        ~SemLock() = default;
    };
    
}

#endif // SEMLOCK_H