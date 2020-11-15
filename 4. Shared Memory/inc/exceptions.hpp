#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

namespace shmem {

    std::string error_string (int);

    class SharedMemoryException: public std::runtime_error {
    public:
        using std::runtime_error::runtime_error;
    };

    class SemaphoreError: public SharedMemoryException {
    public:
        SemaphoreError(int);
    };

    class AllocatorError: public SharedMemoryException {
    public:
        AllocatorError();
    };

    class MMapInitError: public SharedMemoryException {
    public:
        MMapInitError(int);
    };

    class MMapDeInitError: public SharedMemoryException {
    public:
        MMapDeInitError(int);
    };

} // namespace shmem

#endif // EXCEPTIONS_H