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
        evictLFU();

        // update freequency
        auto fit = m_frequency.insert({ it->second.second->first + 1, it->second.second->second});
        m_frequency.erase(it->second.second);
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

            evictLRU();

            auto fit = m_frequency.insert({1, key});
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
    void evictLRU()
    {
        if (m_frequency.empty()) return;

        auto fit = m_frequency.upper_bound(1);
        if (fit == m_frequency.begin()) return;

        std::size_t size = std::distance(m_frequency.begin(), fit);
        if (size == m_lrusize)
        {
            // evict from 1
            auto rit = m_frequency.lower_bound(1);

            if (m_lrughost.size() == m_lrughostsize)
                evictLRUHistory();

            m_ghost.insert({rit->second, rit->first});

            m_cache.erase(rit->second);
            m_frequency.erase(rit);
        }
    }

    void evictLFU()
    {
        if (m_frequency.empty()) return;

        auto fit = m_frequency.upper_bound(1);
        if (fit == m_frequency.end()) return;

        size_t size = std::distance(m_frequency.end(), fit);
        if (size == m_lfusize)
        {
            if (m_lfughost.size() == m_lfughostsize)
                evictLFUHistory();

            m_ghost.insert({fit->second, fit->first});

            m_cache.erase(fit->second);
            m_frequency.erase(fit);
        }
    }

    void evictLRUHistory()
    {
        if (m_ghost.empty()) return;
        if (m_lrughost.empty()) return;

        m_ghost.erase(m_lrughost.front());
        m_lrughost.pop_front();
    }

    void evictLFUHistory()
    {
        if (m_ghost.empty()) return;
        if (m_lfughost.empty()) return;

        m_ghost.erase(m_lfughost.front());
        m_lfughost.pop_front();
    }

    void adaptLRU()
    {
        evictLFU();
        m_lfusize--;
        m_lrusize++;
    }

    void adaptLFU()
    {
        evictLRU();
        m_lrusize--;
        m_lfusize++;
    }

private:
    std::size_t m_lrusize;
    std::size_t m_lrughostsize;

    std::size_t m_lfusize;
    std::size_t m_lfughostsize;

    typedef typename std::multimap<Key, Freequency>::iterator GhostIterator;
    typedef typename std::multimap<Freequency, Key>::iterator FreequencyIterator;

    std::list<GhostIterator> m_lrughost;
    std::list<GhostIterator> m_lfughost;

    std::unordered_map<Key, Freequency> m_ghost;

    std::multimap<Freequency, Key> m_frequency;
    std::unordered_map<Key, std::pair<Value, FreequencyIterator> > m_cache;
};

}
}

#endif // MERE_CACHE_ARCCACHE_H
