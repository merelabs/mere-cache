#ifndef MERE_CACHE_TLRUCACHE_H
#define MERE_CACHE_TLRUCACHE_H

#include "global.h"
#include "cache.h"

#include <list>
#include <unordered_map>
#include <chrono>

namespace Mere
{
namespace Cache
{

typedef std::string Key;
typedef std::string Value;
typedef std::chrono::seconds Age;
typedef std::chrono::time_point<std::chrono::steady_clock> Time;

typedef std::pair<Key, Value> Pair;
typedef std::list<Pair>::iterator PairIterator;

class MERE_CACHE_LIB_SPEC TLRUCache : public Mere::Cache::Cache
{
public:
    ~TLRUCache();
    TLRUCache(int capacity);

    void age(const Age &age);
    Age age() const;

    bool has(const std::string &key) override;
    std::string get(const std::string &key, bool *flag = nullptr) override;
    void set(const std::string &key, const std::string &value, bool *flag = nullptr) override;
    void evict() override;

    void print();

private:
    int m_capacity;
    Age m_age;

    std::list<Pair> m_pairs;
    std::unordered_map<std::string, std::pair<Time, PairIterator>> m_cache;
};

}
}

#endif // MERE_CACHE_TLRUCACHE_H
