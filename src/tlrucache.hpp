#ifndef MERE_CACHE_TLRUCACHE_H
#define MERE_CACHE_TLRUCACHE_H

#include "global.h"
#include "cache.hpp"

#include <list>
#include <unordered_map>
#include <chrono>
#include <iostream>

namespace Mere
{
namespace Cache
{
typedef std::chrono::seconds Age;
typedef std::chrono::time_point<std::chrono::steady_clock> Time;

template <typename Key, typename Value>
class MERE_CACHE_LIB_SPEC TLRUCache : public Mere::Cache::Cache<Key, Value>
{
public:
    TLRUCache(std::size_t capacity)
        : Mere::Cache::Cache<Key, Value>(capacity),
          m_age(60)
    {
    }

    void age(const Age &age)
    {
        m_age = age;
    }

    Age age() const
    {
        return m_age;
    }

    bool has(const Key &key) override
    {
        auto it = m_cache.find(key);
        if( it == m_cache.cend())
            return false;

        auto diff = std::chrono::high_resolution_clock::now() - it->second.first;
        if (m_age > std::chrono::duration_cast<Age>(diff))
        {
            m_pairs.erase(it->second.second);
            m_cache.erase(key);
            return false;
        }

        return true;
    }

    std::string get(const Key &key, bool *flag = nullptr) override
    {
        auto it = m_cache.find(key);
        if (it == m_cache.cend())
        {
            if (flag) *flag = false;
            return "";
        }

        auto diff = std::chrono::high_resolution_clock::now() - it->second.first;
        if (m_age > std::chrono::duration_cast<Age>(diff))
        {
            if (flag) *flag = false;

            m_pairs.erase(it->second.second);
            m_cache.erase(key);
            return "";
        }

        // check if it already in front
        if (std::next(it->second.second) != m_pairs.end())
            m_pairs.splice(m_pairs.end(), m_pairs, it->second.second);

        if (flag) *flag = true;

        return it->second.second->second;
    }

    void set(const Key &key, const Value &value, bool *flag = nullptr) override
    {
        set(key, value, m_age, flag);

//        auto it = m_cache.find(key);
//        if (it == m_cache.cend())
//        {
//            if (flag) *flag = false;

//            if (m_pairs.size() == this->capacity())
//                evict();

//            m_pairs.push_back({key, value});
//        }
//        else
//        {
//            if (flag) *flag = true;
//            if (std::next(it->second.second) != m_pairs.begin())
//                m_pairs.splice(m_pairs.end(), m_pairs, it->second.second);
//        }

//        m_cache.insert({key, {std::chrono::high_resolution_clock::now(), std::prev(m_pairs.end())}});
    }

    void set(const Key &key, const Value &value, const Age &ttu, bool *flag = nullptr)
    {

    }

    void evict() override
    {
        m_cache.erase(m_pairs.front().first);
        m_pairs.pop_front();
    }

    void print()
    {
        for (auto& cache : m_cache)
            std::cout << cache.first << "\t => " << cache.second.second->second << std::endl;
    }

private:
    typedef typename std::pair<Key, Value> Pair;
    typedef typename std::list<Pair>::iterator PairIterator;

    Age m_age;

    std::list<Pair> m_pairs;
    std::unordered_map<Key, std::tuple<Time, Age, PairIterator>> m_cache;
};

}
}

#endif // MERE_CACHE_TLRUCACHE_H
