#include "semaphore.hpp"

namespace shmem {

    Semaphore::Semaphore() {
        ::sem_init(&_value, 1, 1);
    }

    Semaphore::~Semaphore() {
        ::sem_destroy(&_value);
    }

    void Semaphore::unlock() {
        ::sem_post(&_value);
    }

    void Semaphore::lock() {
        ::sem_wait(&_value);
    }

} // namespace shmem