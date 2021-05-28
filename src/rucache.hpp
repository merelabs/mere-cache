#ifndef MERE_CACHE_RUCACHE_H
#define MERE_CACHE_RUCACHE_H

#include "global.h"
#include "cache.hpp"

#include <list>
#include <unordered_map>
#include <iostream>

namespace Mere
{
namespace Cache
{

template <typename Key, typename Value>
class MERE_CACHE_LIB_SPEC RUCache : public Mere::Cache::Cache<Key, Value>
{
public:
    explicit RUCache(std::size_t capacity)
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

        // check if it already in front
        if (std::next(it->second) != m_pairs.end())
            m_pairs.splice(m_pairs.end(), m_pairs, it->second);

        if (flag) *flag = true;
        return it->second->second;
    }

    void set(const Key &key, const Value &value, bool *flag = nullptr) override
    {
        auto it = m_cache.find(key);
        if (it == m_cache.cend())
        {
            if (flag) *flag = false;

            if (m_pairs.size() == this->capacity())
                evict();

            m_pairs.push_back({key, value});
        }
        else
        {
            if (flag) *flag = true;
            if (std::next(it->second) != m_pairs.end())
                m_pairs.splice(m_pairs.end(), m_pairs, it->second);
        }

        m_cache.insert({key, std::prev(m_pairs.end())});
    }

    virtual void evict() override
    {

    }

    void print()
    {
        for (auto& pair : m_pairs)
            std::cout << pair.first << "\t => " << pair.second << std::endl;

        for (auto& cache : m_cache)
            std::cout << cache.first << "\t => " << cache.second->second << std::endl;
    }

protected:
    typedef typename std::pair<Key, Value> Pair;
    typedef typename std::list<Pair>::iterator PairIterator;

    std::list<Pair> m_pairs;
    std::unordered_map<Key, PairIterator> m_cache;

};

}
}

#endif // MERE_CACHE_RUCACHE_H
