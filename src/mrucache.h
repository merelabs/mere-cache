#ifndef MERE_CACHE_MRUCACHE_H
#define MERE_CACHE_MRUCACHE_H

#include "global.h"
#include "cache.h"

#include <list>
#include <unordered_map>

namespace Mere
{
namespace Cache
{

typedef std::pair<std::string, std::string> Pair;
typedef std::list<Pair>::iterator PairIterator;

class MERE_CACHE_LIB_SPEC MRUCache : public Mere::Cache::Cache
{
public:
    ~MRUCache();
    explicit MRUCache(std::size_t capacity);

    bool has(const std::string &key) override;
    std::string get(const std::string &key, bool *flag = nullptr) override;
    void set(const std::string &key, const std::string &value, bool *flag = nullptr) override;
    void evict() override;

    void print();

private:
    std::list<Pair> m_pairs;
    std::unordered_map<std::string, PairIterator> m_cache;

};
}
}

#endif // MERE_CACHE_MRUCACHE_H
