#include "lfucache.h"

Mere::Cache::LFUCache::~LFUCache()
{
}

Mere::Cache::LFUCache::LFUCache(int capacity)
    : m_capacity(capacity)
{
}

bool Mere::Cache::LFUCache::has(const std::string &key)
{
    return m_cache.find(key) != m_cache.cend();
}

std::string Mere::Cache::LFUCache::get(const std::string &key, bool *flag)
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

void Mere::Cache::LFUCache::set(const std::string &key, const std::string &value, bool *flag)
{
    auto it = m_cache.find(key);
    if (it == m_cache.cend())
    {
        if (flag) *flag = false;

        if (m_frequency.size() == m_capacity)
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

void Mere::Cache::LFUCache::evict()
{
    auto fit = m_frequency.begin();
    m_cache.erase(fit->second);
    m_frequency.erase(fit);
}
