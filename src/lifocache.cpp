#include "lifocache.h"
#include <iostream>

template <typename K, typename V>
Mere::Cache::LIFOCache<K, V>::~LIFOCache()
{
}

template <typename K, typename V>
Mere::Cache::LIFOCache<K, V>::LIFOCache(std::size_t capacity)
    : Mere::Cache::Cache<K, V>(capacity)
{
}

template <typename K, typename V>
bool Mere::Cache::LIFOCache<K, V>::has(const K &key)
{
    if (key.empty()) return false;

    return m_cache.find(key) != m_cache.cend();
}

template <typename K, typename V>
V Mere::Cache::LIFOCache<K, V>::get(const K &key, bool *flag)
{
    if (key.empty())
    {
        if (flag) *flag = false;
        return "";
    }

    auto it = m_cache.find(key);
    if (it == m_cache.cend())
    {
        if (flag) *flag = false;
        return "";
    }

    if (flag) *flag = true;
    return it->second;
}

template <typename K, typename V>
void Mere::Cache::LIFOCache<K, V>::set(const K &key, const V &value, bool *flag)
{
    if (key.empty())
    {
        if (flag) *flag = false;
        return;
    }

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

        if (flag) *flag = true;
        m_cache.insert({key, value});
    }
}

template <typename K, typename V>
void Mere::Cache::LIFOCache<K, V>::evict()
{
    m_cache.erase(m_pairs.top());
    m_pairs.pop();
}

template <typename K, typename V>
void Mere::Cache::LIFOCache<K, V>::print()
{
    for (auto& cache : m_cache)
        std::cout << cache.first << "\t => " << cache.second << std::endl;
}
