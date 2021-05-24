#include "arccache.h"

Mere::Cache::ARCCache::~ARCCache()
{

}

Mere::Cache::ARCCache::ARCCache(int capacity)
    : Mere::Cache::Cache(capacity),
      m_lrusize(std::floor(capacity/2)),
      m_lrughostsize(std::floor(capacity/2)),
      m_lfusize(std::ceil(capacity/2)),
      m_lfughostsize(std::ceil(capacity/2))
{
}

bool Mere::Cache::ARCCache::has(const std::string &key)
{
    if (key.empty()) return false;

    return m_cache.find(key) != m_cache.cend();
}

std::string Mere::Cache::ARCCache::get(const std::string &key, bool *flag)
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

        auto hit = m_ghost.find(key);
        if (hit != m_ghost.cend())
        {
            if (hit->second == 1)
                adaptLRU();
            else
                adaptLFU();
        }

        return "";
    }

    // evict if full...
    evictLFU();

    // update freequency
    auto fit = m_frequency.insert({ it->second.second->first + 1, it->second.second->second});
    m_frequency.erase(it->second.second);
    it->second.second = fit;

    if (flag) *flag = true;
    return it->second.first;
}


void Mere::Cache::ARCCache::set(const std::string &key, const std::string &value, bool *flag)
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

        evictLRU();

        auto fit = m_frequency.insert({1, key});
        m_cache.insert({key, {value, fit}});
    }
    else
    {
        if (flag) *flag = true;
        m_cache.insert({key, {value, it->second.second}});
    }
}

void Mere::Cache::ARCCache::evict()
{
}

void Mere::Cache::ARCCache::evictLRU()
{
    if (m_frequency.empty()) return;

    auto fit = m_frequency.upper_bound(1);
    if (fit == m_frequency.begin()) return;

    std::size_t size = std::distance(m_frequency.begin(), fit);
    if (size == m_lrusize)
    {
        // evict from 1
        auto rit = m_frequency.lower_bound(1);

        if (m_lrughost.size() == m_lrughostsize)
            evictLRUHistory();

        m_ghost.insert({rit->second, rit->first});

        m_cache.erase(rit->second);
        m_frequency.erase(rit);
    }
}

void Mere::Cache::ARCCache::evictLFU()
{
    if (m_frequency.empty()) return;

    auto fit = m_frequency.upper_bound(1);
    if (fit == m_frequency.end()) return;

    size_t size = std::distance(m_frequency.end(), fit);
    if (size == m_lfusize)
    {
        if (m_lfughost.size() == m_lfughostsize)
            evictLFUHistory();

        m_ghost.insert({fit->second, fit->first});

        m_cache.erase(fit->second);
        m_frequency.erase(fit);
    }
}

void Mere::Cache::ARCCache::adaptLRU()
{
    evictLFU();
    m_lfusize--;
    m_lrusize++;

}

void Mere::Cache::ARCCache::adaptLFU()
{
    evictLRU();
    m_lrusize--;
    m_lfusize++;
}

void Mere::Cache::ARCCache::evictLRUHistory()
{
    if (m_ghost.empty()) return;
    if (m_lrughost.empty()) return;

    m_ghost.erase(m_lrughost.front());
    m_lrughost.pop_front();
}

void Mere::Cache::ARCCache::evictLFUHistory()
{
    if (m_ghost.empty()) return;
    if (m_lfughost.empty()) return;

    m_ghost.erase(m_lfughost.front());
    m_lfughost.pop_front();
}
