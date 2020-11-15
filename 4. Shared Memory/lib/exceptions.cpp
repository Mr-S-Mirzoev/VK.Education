#include "exceptions.hpp"

#include <cstring>

namespace shmem {

    std::string error_string (int error) {
        return strerror(error);
    }

    SemaphoreError::SemaphoreError(int error_number): 
        SharedMemoryException("Shared memory exception: " + error_string(error_number)) {}

    AllocatorError::AllocatorError():
        SharedMemoryException("Allocation on Shared Memory failed.") {}

    MMapInitError::MMapInitError(int error_number):
        SharedMemoryException("Mmap initialization error: " + error_string(error_number)) {}

    MMapDeInitError::MMapDeInitError(int error_number):
        SharedMemoryException("MMap deinitialization error: " + error_string(error_number)) {}

    

} // namespace shmem