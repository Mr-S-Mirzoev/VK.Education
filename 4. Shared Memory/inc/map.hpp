#ifndef SHMEM_MAP_H
#define SHMEM_MAP_H

#include <map>
#include <utility>
#include <functional>

#include "semlock.hpp"
#include "allocator.hpp"
#include "semaphore.hpp"

namespace shmem {

    template <class K, class V> 
    class SharedMap {
    public:
        SharedMap(size_t block_size, size_t blocks_count);
        void update (const K &key, const V &new_value);
        void insert (const K &key, const V &value);
        V get(const K &key);
        void remove(const K &key); 
        using value_type = typename std::map<K, V>::value_type;
    private:
        Semaphore *_sem;
        ShMemState *_state;

        char *_mmap;
        std::map <K, V, std::less<K>, ShAlloc<value_type>> *_map;
    };

}  // namespace shmem

#endif  // SHMEM_MAP_H