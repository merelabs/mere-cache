#ifndef MERE_CACHE_FUCACHE_HPP
#define MERE_CACHE_FUCACHE_HPP

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
class MERE_CACHE_LIB_SPEC FUCache : public Mere::Cache::Cache<Key, Value>
{
public:
    explicit FUCache(std::size_t capacity)
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

    virtual void evict() override
    {
    }

    void print();

protected:
    typedef typename std::multimap<Freequency, Key>::iterator  FreequencyIterator;
    std::multimap<Freequency, Key> m_frequency;
    std::unordered_map<Key, std::pair<Value, FreequencyIterator> > m_cache;
};
}
}


#endif // MERE_CACHE_FUCACHE_HPP
