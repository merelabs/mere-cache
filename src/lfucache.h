#ifndef MERE_CACHE_LFUCACHE_H
#define MERE_CACHE_LFUCACHE_H

#include "global.h"
#include "cache.h"

#include <map>
#include <unordered_map>

namespace Mere
{
namespace Cache
{

typedef std::string Key;
typedef std::string Value;
typedef unsigned int Freequency;

typedef  std::multimap<Freequency, Key>::iterator  FreequencyIterator;

class LFUCache : public Mere::Cache::Cache
{
public:
    ~LFUCache();
    explicit LFUCache(int capacity);

    bool has(const std::string &key) override;
    std::string get(const std::string &key, bool *flag = nullptr) override;
    void set(const std::string &key, const std::string &value, bool *flag = nullptr) override;
    void evict() override;

    void print();

private:
    int m_capacity;

    std::multimap<Freequency, Key> m_frequency;
    std::unordered_map<Key, std::pair<Value, FreequencyIterator> > m_cache;
};

}
}
#endif // MERE_CACHE_LFUCACHE_H
