#ifndef SEMLOCK_H
#define SEMLOCK_H

namespace shmem {
    class SemLock {
        Semaphore &_threshold;
    public:
        SemLock(Semaphore &threshold);
        ~SemLock();
    };
}

#endif // SEMLOCK_H