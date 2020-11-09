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

namespace {

    size_t get_size_in_blocks(size_t bytes, size_t block_size) {
        float blocks_needed = bytes / static_cast<float>(block_size);
        return std::ceil(blocks_needed);
    }

    size_t find_free_blocks(size_t blocks_count, const std::string_view& used_table) {
        std::string pattern(blocks_count, FREE_BLOCK);
        size_t pos = used_table.find(pattern);
        if(pos == std::string::npos) {
            throw std::bad_alloc{};
        }
        return pos;
    }

} // namespace

namespace shmem {

    struct ShMemState {
        size_t blocks_count;
        size_t block_size;
        char* used_blocks_table;
        char* first_block;
    };

    template<typename T>
    class ShAlloc {
    public:
        typedef T value_type;

        explicit ShAlloc(ShMemState* state)
            : state_{state} {}

        template<class U>
        ShAlloc(const ShAlloc<U>& other) noexcept {
            state_ = other.state_;
        }

        T* allocate(std::size_t n) {
            size_t blocks_needed = get_size_in_blocks(sizeof(T) * n, state_->block_size);
            std::string_view table{state_->used_blocks_table, state_->blocks_count};
            size_t blocks_pos = find_free_blocks(blocks_needed, table);
            ::memset(state_->used_blocks_table + blocks_pos, USED_BLOCK, blocks_needed);
            return reinterpret_cast<T*>(state_->first_block + blocks_pos * state_->block_size);
        }

        void deallocate(T* p, std::size_t n) noexcept {
            size_t offset = (reinterpret_cast<char*>(p) - state_->first_block) / state_->block_size;
            size_t blocks_count = get_size_in_blocks(sizeof(T) * n, state_->block_size);
            ::memset(state_->used_blocks_table + offset, FREE_BLOCK, blocks_count);
        }

        ShMemState* state_;
    };

    template <class T, class U>
    bool operator==(const ShAlloc<T>&a, const ShAlloc<U>&b) {
        return a.state_ == b.state_;
    }

    template <class T, class U>
    bool operator!=(const ShAlloc<T>&a, const ShAlloc<U>&b) {
        return a.state_ != b.state_;
    }
} // namespace shmem