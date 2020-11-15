#include "semaphore.hpp"
#include "exceptions.hpp"

namespace shmem {

    Semaphore::Semaphore(): _value(sizeof(::sem_t)) {
        if (::sem_init(_value.get_addr(), 0, 1) == -1)
            throw SemaphoreError{errno};
    }

    Semaphore::~Semaphore() {
        if (::sem_destroy(_value.get_addr()) == -1) 
            throw SemaphoreError(errno);

    }

    void Semaphore::unlock() {
        if (::sem_post(_value.get_addr()) == -1)
            throw SemaphoreError(errno);
    }

    void Semaphore::lock() {
        if (::sem_wait(_value.get_addr()) == -1)
            throw SemaphoreError(errno);
    }

} // namespace shmem