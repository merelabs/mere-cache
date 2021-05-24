#include "mrucache.h"

Mere::Cache::MRUCache::~MRUCache()
{
}

Mere::Cache::MRUCache::MRUCache(std::size_t capacity)
    : Mere::Cache::Cache(capacity)
{

}

bool Mere::Cache::MRUCache::has(const std::string &key)
{
    if (key.empty()) return false;

    return m_cache.find(key) != m_cache.cend();
}

std::string Mere::Cache::MRUCache::get(const std::string &key, bool *flag)
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

void Mere::Cache::MRUCache::set(const std::string &key, const std::string &value, bool *flag)
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

