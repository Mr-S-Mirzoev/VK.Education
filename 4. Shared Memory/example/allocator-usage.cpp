#include "allocator.hpp"
#include "semaphore.hpp"
#include "semlock.hpp"

using CharAlloc = shmem::ShAlloc<char>;
using ShString = std::basic_string<char, std::char_traits<char>, CharAlloc>;
using ShUPtr = std::unique_ptr<char, std::function<void(char*)>>;

int main()
{
    size_t blocks_count = 100;
    size_t block_size = 128;
    size_t shmem_size = blocks_count * block_size;
    void* mmap = ::mmap(0, shmem_size,
                        PROT_READ | PROT_WRITE,
                        MAP_ANONYMOUS | MAP_SHARED,
                        -1, 0);

    if (mmap == MAP_FAILED) {
        std::cerr << "Failed to create shared map" << std::endl;
        return 1;
    }

    ShUPtr shmem{static_cast<char*>(mmap),
                [shmem_size](char* shmem) { ::munmap(shmem, shmem_size); }};

    shmem::ShMemState* state = new(shmem.get()) shmem::ShMemState{};

    float header_size = (sizeof(shmem::ShMemState) + blocks_count) / static_cast<float>(block_size);
    state->block_size = block_size;
    state->blocks_count = blocks_count - std::floor(header_size);
    state->used_blocks_table = shmem.get() + sizeof(shmem::ShMemState);
    state->first_block = state->used_blocks_table + state->blocks_count;
    ::memset(state->used_blocks_table, FREE_BLOCK, state->blocks_count);

    shmem::ShAlloc<ShString> alloc{state};
    ShString* string = new(alloc.allocate(1)) ShString{alloc};
/*
    int fork = ::fork();
    if (fork == 0) {
        *string = "Hello from Child!";
        return 0;
    }
    ::waitpid(fork, nullptr, 0);
    std::cout << *string << std::endl;
*/  
    shmem::Semaphore s;
    shmem::SemLock lock(s);

    if (::fork() == 0) {
        std::cout << "C" << std::endl;
        *string = "Hello from child";
    } else {
        shmem::SemLock lock2(s);
        std::cout << "F" << std::endl;
        std::cout << *string << std::endl;
    }
    return 0;
}