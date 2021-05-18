#include "lrucache.h"
#include <iostream>
#include <algorithm>
#include <chrono>

Mere::Cache::LRUCache::LRUCache(int capacity)
    : m_capacity(capacity)
{

}

bool Mere::Cache::LRUCache::has(const std::string &key) const
{
    return m_cache.find(key) != m_cache.cend();
}

std::string Mere::Cache::LRUCache::get(const std::string &key, bool *flag)
{
    auto it = m_cache.find(key);
    if (it == m_cache.cend())
    {
        if (flag) *flag = false;
        return "";
    }

    // check if it already in front
    if (it->second != m_refs.begin())
        m_refs.splice(m_refs.begin(), m_refs, it->second);

    if (flag) *flag = true;
    return m_refs.front().second;
}

void Mere::Cache::LRUCache::set(const std::string &key, const std::string &value, bool *flag)
{
    auto it = m_cache.find(key);
    if (it == m_cache.cend())
    {
        if (flag) *flag = false;

        m_refs.push_front({key, value});
        if (m_refs.size() > m_capacity)
        {
            auto it = std::prev(m_refs.end());
            m_cache.erase(it->first);
            m_refs.pop_back();
        }
    }
    else
    {
        if (flag) *flag = true;
        if (it->second != m_refs.begin())
            m_refs.splice(m_refs.begin(), m_refs, it->second);
    }

    m_cache.insert({key, m_refs.begin()});
}

void Mere::Cache::LRUCache::print()
{
    for (auto& key : m_cache)
        std::cout << key.first << "\t => " << key.second->second << std::endl;
}
