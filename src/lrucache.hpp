#ifndef MERE_CACHE_LRUCACHE_H
#define MERE_CACHE_LRUCACHE_H

#include "global.h"
#include "rucache.hpp"

#include <list>
#include <unordered_map>
#include <iostream>

namespace Mere
{
namespace Cache
{

template <typename Key, typename Value>
class MERE_CACHE_LIB_SPEC LRUCache : public Mere::Cache::RUCache<Key, Value>
{
public:
    explicit LRUCache(std::size_t capacity)
        : Mere::Cache::RUCache<Key, Value>(capacity)
    {
    }

    void evict() override
    {
        if (RUCache<Key, Value>::m_cache.empty()) return;
        if (RUCache<Key, Value>::m_pairs.empty()) return;

        RUCache<Key, Value>::m_cache.erase(RUCache<Key, Value>::m_pairs.front().first);
        RUCache<Key, Value>::m_pairs.pop_front();
    }
};
}
}

#endif // MERE_CACHE_LRUCACHE_H
