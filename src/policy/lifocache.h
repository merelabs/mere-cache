#ifndef MERE_CACHE_LIFOCACHE_H
#define MERE_CACHE_LIFOCACHE_H

#include "../global.h"
#include "../cache.h"

#include <stack>
#include <unordered_map>

namespace Mere
{
namespace Cache
{
namespace Policy
{

typedef std::string Key;
typedef std::string Value;

typedef std::unordered_map<Key, Value>::iterator CacheIterator;

class MERE_CACHE_LIB_SPEC LIFOCache : public Mere::Cache::Cache
{
public:
    ~LIFOCache();
    explicit LIFOCache(int capacity);

    bool has(const std::string &key) override;
    std::string get(const std::string &key, bool *flag = nullptr) override;
    void set(const std::string &key, const std::string &value, bool *flag = nullptr) override;
    void evict() override;

    void print();

private:
    int m_capacity;

    std::stack<CacheIterator> m_pairs;
    std::unordered_map<Key, Value> m_cache;
};

}
}
}

#endif // MERE_CACHE_LIFOCACHE_H
