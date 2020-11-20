#include "semlock.hpp"

namespace shmem {

    SemLock::SemLock(Semaphore &sem): _threshold(sem) {
        _threshold.lock();
    }

    SemLock::~SemLock() {
        _threshold.unlock();
    }

} // namespace shmem