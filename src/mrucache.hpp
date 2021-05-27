#ifndef MERE_CACHE_MRUCACHE_H
#define MERE_CACHE_MRUCACHE_H

#include "global.h"
#include "rucache.hpp"

#include <list>
#include <unordered_map>

namespace Mere
{
namespace Cache
{

template <typename Key, typename Value>
class MERE_CACHE_LIB_SPEC MRUCache : public Mere::Cache::RUCache<Key, Value>
{
public:
    explicit MRUCache(std::size_t capacity)
        : Mere::Cache::Cache<Key, Value>(capacity)
    {

    }

    void evict() override
    {
        if (RUCache<Key, Value>::m_cache.empty()) return;
        if (RUCache<Key, Value>::m_pairs.empty()) return;

        RUCache<Key, Value>::m_cache.erase(RUCache<Key, Value>::m_pairs.back().first);
        RUCache<Key, Value>::m_pairs.pop_back();
    }
};
}
}

#endif // MERE_CACHE_MRUCACHE_H
