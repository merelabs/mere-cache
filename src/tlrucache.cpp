#include "tlrucache.h"
#include <iostream>

Mere::Cache::TLRUCache::~TLRUCache()
{
}

Mere::Cache::TLRUCache::TLRUCache(std::size_t capacity)
    : Mere::Cache::Cache(capacity),
      m_age(60)
{
}

void Mere::Cache::TLRUCache::age(const Age &age)
{
    m_age = age;
}

Mere::Cache::Age Mere::Cache::TLRUCache::age() const
{
    return m_age;
}

bool Mere::Cache::TLRUCache::has(const std::string &key)
{
    if (key.empty()) return false;

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

std::string Mere::Cache::TLRUCache::get(const std::string &key, bool *flag)
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

void Mere::Cache::TLRUCache::set(const std::string &key, const std::string &value, bool *flag)
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
        if (std::next(it->second.second) != m_pairs.begin())
            m_pairs.splice(m_pairs.end(), m_pairs, it->second.second);
    }

    m_cache.insert({key, {std::chrono::high_resolution_clock::now(), std::prev(m_pairs.end())}});
}

void Mere::Cache::TLRUCache::evict()
{
    m_cache.erase(m_pairs.front().first);
    m_pairs.pop_front();
}

void Mere::Cache::TLRUCache::print()
{
    for (auto& cache : m_cache)
        std::cout << cache.first << "\t => " << cache.second.second->second << std::endl;
}
