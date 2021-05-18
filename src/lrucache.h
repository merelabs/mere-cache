#ifndef MERE_CACHE_LRUCACHE_H
#define MERE_CACHE_LRUCACHE_H

#include "global.h"
#include "cache.h"

#include <unordered_map>

namespace Mere
{
namespace Cache
{

typedef std::list<std::pair<std::string, std::string>>::iterator PairIterator;
//struct PairHash
//{
//    size_t operator()(const PairIterator &that) const
//    {
//        return std::hash<std::pair, std::string>()(*that);
//    }
//};

class MERE_CACHE_LIB_SPEC LRUCache : public Mere::Cache::Cache
{
public:
    explicit LRUCache(int capacity);

    bool has(const std::string &key) const override;
    std::string get(const std::string &key, bool *flag = nullptr) override;
    void set(const std::string &key, const std::string &value, bool *flag = nullptr) override;

    void print();

private:
    int m_capacity;

    std::list<std::pair<std::string, std::string>> m_refs;
    std::unordered_map<std::string, PairIterator> m_cache;
};

}
}

#endif // MERE_CACHE_LRUCACHE_H
