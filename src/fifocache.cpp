#include "fifocache.h"

#include <iostream>
Mere::Cache::FIFOCache::~FIFOCache()
{
}

Mere::Cache::FIFOCache::FIFOCache(std::size_t capacity)
    : Mere::Cache::Cache(capacity)
{
}

bool Mere::Cache::FIFOCache::has(const std::string &key)
{
    if (key.empty()) return false;

    return m_cache.find(key) != m_cache.cend();
}

std::string Mere::Cache::FIFOCache::get(const std::string &key, bool *flag)
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

void Mere::Cache::FIFOCache::set(const std::string &key, const std::string &value, bool *flag)
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

        if (m_pairs.size() == capacity())
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

void Mere::Cache::FIFOCache::evict()
{
    if (m_cache.empty()) return;
    if (m_pairs.empty()) return;

    m_cache.erase(m_pairs.front());
    m_pairs.pop();
}

void Mere::Cache::FIFOCache::print()
{
    for (auto& cache : m_cache)
        std::cout << cache.first << "\t => " << cache.second << std::endl;
}
