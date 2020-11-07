#include <iostream>
#include <memory>
#include <cmath>
#include <cerrno>
#include <cstring>
#include <functional>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

constexpr char USED_BLOCK = '1';
constexpr char FREE_BLOCK = '0';

namespace shmem {
    struct ShMemState {
        size_t blocks_count;
        size_t block_size;
        char* used_blocks_table;
        char* first_block;
    };

    template<typename T>
    class ShAlloc
    {
    public:
        typedef T value_type;

        explicit ShAlloc(ShMemState* state)
            : state_{state} {}

        template<class U>
        ShAlloc(const ShAlloc<U>& other) noexcept {
            state_ = other.state_;
        }

        T* allocate(std::size_t n);

        void deallocate(T* p, std::size_t n) noexcept;

        ShMemState* state_;
    };

    template <class T, class U>
    bool operator==(const ShAlloc<T>&a, const ShAlloc<U>&b);

    template <class T, class U>
    bool operator!=(const ShAlloc<T>&a, const ShAlloc<U>&b);
}