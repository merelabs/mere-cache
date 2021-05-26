#ifndef MERE_CACHE_LIFOCACHE_H
#define MERE_CACHE_LIFOCACHE_H

#include "global.h"
#include "cache.h"

#include <stack>
#include <unordered_map>

namespace Mere
{
namespace Cache
{

//typedef std::unordered_map<Key, Value>::iterator CacheIterator;

template <typename K, typename V>
class MERE_CACHE_LIB_SPEC LIFOCache : public Mere::Cache::Cache<K, V>
{
public:
    ~LIFOCache();
    explicit LIFOCache(std::size_t capacity);

    bool has(const K &key) override;
    V get(const K &key, bool *flag = nullptr) override;
    void set(const K &key, const V &value, bool *flag = nullptr) override;
    void evict() override;

    void print();

private:
    typedef typename std::unordered_map<K, V>::iterator CacheIterator;

    std::stack<CacheIterator> m_pairs;
    std::unordered_map<K, V> m_cache;
};

}
}

#endif // MERE_CACHE_LIFOCACHE_H
