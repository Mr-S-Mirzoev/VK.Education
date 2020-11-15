#include "semlock.hpp"

namespace shmem {

    SemLock::SemLock(Semaphore &sem): _threshold(sem) {}

} // namespace shmem