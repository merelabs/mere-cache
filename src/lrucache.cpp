#include "lrucache.h"
#include <iostream>

Mere::Cache::LRUCache::~LRUCache()
{
}

Mere::Cache::LRUCache::LRUCache(std::size_t capacity)
    : Mere::Cache::Cache(capacity)
{
}

bool Mere::Cache::LRUCache::has(const std::string &key)
{
    if (key.empty()) return false;

    return m_cache.find(key) != m_cache.cend();
}

std::string Mere::Cache::LRUCache::get(const std::string &key, bool *flag)
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

    // check if it already in front
    if (std::next(it->second) != m_pairs.end())
        m_pairs.splice(m_pairs.end(), m_pairs, it->second);

    if (flag) *flag = true;
    return it->second->second;
}

void Mere::Cache::LRUCache::set(const std::string &key, const std::string &value, bool *flag)
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

void Mere::Cache::LRUCache::evict()
{
    if (m_cache.empty()) return;
    if (m_pairs.empty()) return;

    m_cache.erase(m_pairs.front().first);
    m_pairs.pop_front();
}

void Mere::Cache::LRUCache::print()
{
    for (auto& cache : m_cache)
        std::cout << cache.first << "\t => " << cache.second->second << std::endl;
}
