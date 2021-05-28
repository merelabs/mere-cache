#ifndef MERE_CACHE_LFUCACHE_H
#define MERE_CACHE_LFUCACHE_H

#include "global.h"
#include "cache.hpp"

#include <map>
#include <unordered_map>

namespace Mere
{
namespace Cache
{

typedef unsigned int Freequency;


template <typename Key, typename Value>
class MERE_CACHE_LIB_SPEC LFUCache : public Mere::Cache::Cache<Key, Value>
{
public:
    explicit LFUCache(std::size_t capacity)
        : Mere::Cache::Cache<Key, Value>(capacity)
    {
    }

    bool has(const std::string &key) override
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

        // update freequency
        auto fit = m_frequency.insert({ it->second.second->first + 1, it->second.second->second});
        m_frequency.erase(it->second.second);
        it->second.second = fit;

        if (flag) *flag = true;
        return it->second.first;
    }

    void set(const Key &key, const Value &value, bool *flag = nullptr) override
    {
        auto it = m_cache.find(key);
        if (it == m_cache.cend())
        {
            if (flag) *flag = false;

            if (m_frequency.size() == this->capacity())
                evict();

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
        auto fit = m_frequency.begin();
        m_cache.erase(fit->second);
        m_frequency.erase(fit);
    }

    void print();

private:
    typedef typename std::multimap<Freequency, Key>::iterator  FreequencyIterator;
    std::multimap<Freequency, Key> m_frequency;
    std::unordered_map<Key, std::pair<Value, FreequencyIterator> > m_cache;
};
}
}
#endif // MERE_CACHE_LFUCACHE_H
