#ifndef SHMEM_MAP_H
#define SHMEM_MAP_H
#include <map>
#include <utility>
#include <functional>

#include "semlock.hpp"
#include "allocator.hpp"
#include "semaphore.hpp"

namespace shmem {

    
    /*

    allblocks_size = blocks_size * block_count;

{      Semaphore    |     ShMemState     | BlockTable  |            ShMap          |    Blocks      }
{_sizeof(semaphore)_|_sizeof(ShMemState)_|_block_count_|_sizeof(ShMap<Key, Value>)_|_allblocks_size_}

    */

    template <class K, class V> 
    class SharedMap {
        char *_mmap;
        std::map *_map;
        Semaphore *_sem;
    public:
        SharedMap(size_t block_size, size_t blocks_count);
        void update (const K &key, const V &new_value);
        void insert (const K &key, const V &value);
        V get(const K &key);
        void remove(const K &key); 
    }

}  // namespace shmem

#endif  // SHMEM_MAP_H