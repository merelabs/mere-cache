#ifndef MERE_CACHE_LRUCACHE_H
#define MERE_CACHE_LRUCACHE_H

#include "../global.h"
#include "../cache.h"

#include <list>
#include <unordered_map>

namespace Mere
{
namespace Cache
{
namespace Policy
{

typedef std::string Key;
typedef std::string Value;

typedef std::pair<Key, Value> Pair;
typedef std::list<Pair>::iterator PairIterator;

class MERE_CACHE_LIB_SPEC LRUCache : public Mere::Cache::Cache
{
public:
    ~LRUCache();
    explicit LRUCache(int capacity);

    bool has(const std::string &key) override;
    std::string get(const std::string &key, bool *flag = nullptr) override;
    void set(const std::string &key, const std::string &value, bool *flag = nullptr) override;
    void evict() override;

    void print();

private:
    int m_capacity;

    std::list<Pair> m_pairs;
    std::unordered_map<Key, PairIterator> m_cache;
};

}
}
}

#endif // MERE_CACHE_LRUCACHE_H
