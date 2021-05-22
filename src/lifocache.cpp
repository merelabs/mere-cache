#include "lifocache.h"

#include <iostream>
#include <algorithm>

Mere::Cache::LIFOCache::~LIFOCache()
{
}

Mere::Cache::LIFOCache::LIFOCache(int capacity)
    : m_capacity(capacity)
{
}

bool Mere::Cache::LIFOCache::has(const std::string &key)
{
    if (key.empty()) return false;

    return m_cache.find(key) != m_cache.cend();
}

std::string Mere::Cache::LIFOCache::get(const std::string &key, bool *flag)
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

void Mere::Cache::LIFOCache::set(const std::string &key, const std::string &value, bool *flag)
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

        if (m_pairs.size() == m_capacity)
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

void Mere::Cache::LIFOCache::evict()
{
    m_cache.erase(m_pairs.top());
    m_pairs.pop();
}

void Mere::Cache::LIFOCache::print()
{
    for (auto& cache : m_cache)
        std::cout << cache.first << "\t => " << cache.second << std::endl;
}
