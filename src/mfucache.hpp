#ifndef MERE_CACHE_MFUCACHE_H
#define MERE_CACHE_MFUCACHE_H

#include "global.h"
#include "fucache.hpp"

namespace Mere
{
namespace Cache
{

typedef unsigned int Freequency;


template <typename Key, typename Value>
class MERE_CACHE_LIB_SPEC MFUCache : public Mere::Cache::FUCache<Key, Value>
{
public:
    explicit MFUCache(std::size_t capacity)
        : Mere::Cache::FUCache<Key, Value>(capacity)
    {
    }

    void evict() override
    {
        if (Mere::Cache::FUCache<Key, Value>::m_cache.empty()) return;
        if (Mere::Cache::FUCache<Key, Value>::m_frequency.empty()) return;

        auto fit = std::prev(Mere::Cache::FUCache<Key, Value>::m_frequency.end());
        Mere::Cache::FUCache<Key, Value>::m_cache.erase(fit->second);
        Mere::Cache::FUCache<Key, Value>::m_frequency.erase(fit);
    }

    void print();
};
}
}

#endif // MERE_CACHE_MFUCACHE_H
