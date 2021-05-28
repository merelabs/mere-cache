#ifndef MERE_CACHE_ARCCACHE_H
#define MERE_CACHE_ARCCACHE_H

#include "global.h"
#include "cache.hpp"

#include <map>
#include <list>
#include <unordered_map>

namespace Mere
{
namespace Cache
{
typedef std::size_t Freequency;

template <typename Key, typename Value>
class MERE_CACHE_LIB_SPEC ARCCache : public Mere::Cache::Cache<Key, Value>
{
public:
    explicit ARCCache(int capacity)
        : Mere::Cache::Cache<Key, Value>(capacity),
          m_lrusize(std::floor(capacity/2)),
          m_lrughostsize(std::floor(capacity/2)),
          m_lfusize(std::ceil(capacity/2)),
          m_lfughostsize(std::ceil(capacity/2))
    {

    }

    bool has(const std::string &key) override
    {
        return m_cache.find(key) != m_cache.cend();
    }

    std::string get(const std::string &key, bool *flag = nullptr) override
    {
        auto it = m_cache.find(key);
        if (it == m_cache.cend())
        {
            if (flag) *flag = false;

            auto hit = m_ghost.find(key);
            if (hit != m_ghost.cend())
            {
                if (hit->second == 1)
                    adaptLRU();
                else
                    adaptLFU();
            }

            return "";
        }

        // evict if full...
        evictLFUCache();

        // update freequency
        auto fit = m_cacheFrequency.insert({ it->second.second->first + 1, it->second.second->second});
        m_cacheFrequency.erase(it->second.second);
        it->second.second = fit;

        if (flag) *flag = true;
        return it->second.first;
    }

    void set(const std::string &key, const std::string &value, bool *flag = nullptr) override
    {
        auto it = m_cache.find(key);
        if (it == m_cache.cend())
        {
            if (flag) *flag = false;

            evictLRUCache();

            auto fit = m_cacheFrequency.insert({1, key});
            m_cache.insert({key, {value, fit}});
        }
        else
        {
            if (flag) *flag = true;
            m_cache.insert({key, {value, it->second.second}});
        }
    }

    void evict() override
    {

    }

    void print();

private:
    void evictLRUCache()
    {
        if (lrusize() == m_lrusize)
        {
            // evict from 1
            auto rit = m_cacheFrequency.lower_bound(1);

            if (lrughostsize() == m_lrughostsize)
                evictLRUGhost();

            m_ghost.insert({rit->second, rit->first});

            m_cache.erase(rit->second);
            m_cacheFrequency.erase(rit);
        }
    }

    void evictLFUCache()
    {
        if (lfusize() == m_lfusize)
        {
            if (lfughostsize() == m_lfughostsize)
                evictLFUGhost();

            auto fit = m_cacheFrequency.upper_bound(1);
            m_ghost.insert({fit->second, fit->first});

            m_cache.erase(fit->second);
            m_cacheFrequency.erase(fit);
        }
    }

    void evictLRUGhost()
    {
        if (lrughostsize() != m_lrughostsize)
            return;

        auto rit = m_ghostFrequency.begin();
        m_ghost.erase(rit->second);
        m_ghostFrequency.erase(rit);
    }

    void evictLFUGhost()
    {
        if (lfughostsize() != m_lfughostsize)
            return;

        auto fit = m_ghostFrequency.upper_bound(1);
        m_ghost.erase(fit->second);
        m_ghostFrequency.erase(fit);
    }

    void adaptLRU()
    {
        evictLFUCache();
        m_lfusize--;
        m_lrusize++;
    }

    void adaptLFU()
    {
        evictLRUCache();
        m_lrusize--;
        m_lfusize++;
    }

    std::size_t lrusize() const
    {
        auto fit = m_cacheFrequency.upper_bound(1);
        if (fit == m_cacheFrequency.begin()) return 0;

        return std::distance(m_cacheFrequency.begin(), fit);
    }

    std::size_t lfusize() const
    {
        auto fit = m_cacheFrequency.upper_bound(1);
        if (fit == m_cacheFrequency.end()) return 0;

        return std::distance(m_cacheFrequency.end(), fit);
    }

    std::size_t lrughostsize() const
    {
        auto fit = m_ghostFrequency.upper_bound(1);
        if (fit == m_ghostFrequency.begin()) return 0;

        return std::distance(m_ghostFrequency.begin(), fit);
    }

    std::size_t lfughostsize() const
    {
        auto fit = m_ghostFrequency.upper_bound(1);
        if (fit == m_ghostFrequency.end()) return 0;

        return std::distance(m_ghostFrequency.end(), fit);
    }

private:
    std::size_t m_lrusize;
    std::size_t m_lrughostsize;

    std::size_t m_lfusize;
    std::size_t m_lfughostsize;

    typedef typename std::multimap<Freequency, Key>::iterator FreequencyIterator;

    std::multimap<Freequency, Key> m_ghostFrequency;
    std::unordered_map<Key, FreequencyIterator> m_ghost;

    std::multimap<Freequency, Key> m_cacheFrequency;
    std::unordered_map<Key, std::pair<Value, FreequencyIterator> > m_cache;
};

}
}

#endif // MERE_CACHE_ARCCACHE_H
