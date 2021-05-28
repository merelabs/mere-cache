#ifndef MERE_CACHE_FIFOCACHE_H
#define MERE_CACHE_FIFOCACHE_H

#include "global.h"
#include "cache.hpp"

#include <queue>
#include <unordered_map>
#include <iostream>

namespace Mere
{
namespace Cache
{

template <typename Key, typename Value>
class MERE_CACHE_LIB_SPEC FIFOCache : public Mere::Cache::Cache<Key, Value>
{
public:
    explicit FIFOCache(std::size_t capacity)
        : Mere::Cache::Cache<Key, Value>(capacity)
    {
    }

    bool has(const Key &key) override
    {
        return m_cache.find(key) != m_cache.cend();
    }

    Value get(const Key &key, bool *flag = nullptr) override
    {
        auto it = m_cache.find(key);
        if (it == m_cache.cend())
        {
            if (flag) *flag = false;
            return "";
        }

        if (flag) *flag = true;

        return it->second;
    }

    void set(const Key &key, const Value &value, bool *flag = nullptr) override
    {
        auto it = m_cache.find(key);
        if (it == m_cache.cend())
        {
            if (flag) *flag = false;

        if (m_pairs.size() == this->capacity())
            evict();

            auto pair = m_cache.insert({key, value});
            m_pairs.push(pair.first);
        }
        else
        {
            if (flag) *flag = true;
            m_cache.insert({key, value});

            // do we need to change the position in queue?
        }
    }

    void evict() override
    {
        if (m_cache.empty()) return;
        if (m_pairs.empty()) return;

        m_cache.erase(m_pairs.front());
        m_pairs.pop();
    }

    void print()
    {
        for (auto& cache : m_cache)
            std::cout << cache.first << "\t => " << cache.second << std::endl;
    }

private:
    typedef typename std::unordered_map<Key, Value>::iterator CacheIterator;
    std::queue<CacheIterator> m_pairs;
    std::unordered_map<Key, Value> m_cache;
};

}
}

#endif // MERE_CACHE_FIFOCACHE_H
