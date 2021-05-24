#ifndef MERE_CACHE_ARCCACHE_H
#define MERE_CACHE_ARCCACHE_H

#include "global.h"
#include "cache.h"

#include <map>
#include <list>
#include <unordered_set>
#include <unordered_map>

namespace Mere
{
namespace Cache
{

typedef std::string Key;
typedef std::string Value;
typedef std::size_t Freequency;

typedef std::pair<Key, Value> Pair;
typedef std::list<Pair>::iterator PairIterator;

typedef std::multimap<Freequency, Key>::iterator  FreequencyIterator;
typedef std::list<FreequencyIterator>::iterator ListIterator;
typedef std::multimap<Key, Freequency>::iterator GhostIterator;

class MERE_CACHE_LIB_SPEC ARCCache : public Mere::Cache::Cache
{
public:
    ~ARCCache();
    explicit ARCCache(int capacity);

    bool has(const std::string &key) override;
    std::string get(const std::string &key, bool *flag = nullptr) override;
    void set(const std::string &key, const std::string &value, bool *flag = nullptr) override;
    void evict() override;

    void print();

private:
    void evictLRUHistory();
    void evictLFUHistory();

    void evictLRU();
    void evictLFU();

    void adaptLRU();
    void adaptLFU();

private:
    std::size_t m_capacity;

    std::size_t m_lrusize;
    std::size_t m_lrughostsize;

    std::size_t m_lfusize;
    std::size_t m_lfughostsize;

    std::list<GhostIterator> m_lrughost;
    std::list<GhostIterator> m_lfughost;
    std::multimap<Key, Freequency> m_ghost;

    std::multimap<Freequency, Key> m_frequency;
    std::unordered_map<Key, std::pair<Value, FreequencyIterator> > m_cache;
};

}
}

#endif // MERE_CACHE_ARCCACHE_H
