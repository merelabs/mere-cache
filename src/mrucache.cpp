#include "mrucache.h"

Mere::Cache::MRUCache::~MRUCache()
{

}

Mere::Cache::MRUCache::MRUCache(int capacity)
    : m_capacity(capacity)
{

}

bool Mere::Cache::MRUCache::has(const std::string &key)
{
    return m_cache.find(key) != m_cache.cend();
}

std::string Mere::Cache::MRUCache::get(const std::string &key, bool *flag)
{
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

void Mere::Cache::MRUCache::set(const std::string &key, const std::string &value, bool *flag)
{
    auto it = m_cache.find(key);
    if (it == m_cache.cend())
    {
        if (flag) *flag = false;

        if (m_pairs.size() == m_capacity)
            evict();

        m_pairs.push_front({key, value});
    }
    else
    {
        if (flag) *flag = true;
        if (std::next(it->second) != m_pairs.end())
            m_pairs.splice(m_pairs.end(), m_pairs, it->second);
    }

    m_cache.insert({key, m_pairs.begin()});
}

void Mere::Cache::MRUCache::evict()
{
    m_cache.erase(m_pairs.back().first);
    m_pairs.pop_back();
}

