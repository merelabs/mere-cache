#ifndef MERE_CACHE_SOFTLINKCACHE_H
#define MERE_CACHE_SOFTLINKCACHE_H

#include "global.h"
#include "diskcache.h"
#include <map>

namespace Mere
{
namespace Cache
{

class LRUCache;

class MERE_CACHE_LIB_SPEC SoftLinkCache : public DiskCache
{
public:
    virtual ~SoftLinkCache();
    SoftLinkCache();
    explicit SoftLinkCache(const std::string &path);

    std::string get(const std::string &key, bool *flag = nullptr);
    void set(const std::string &key, const std::string &link);

    void setCache(LRUCache *cache);

private:
    LRUCache *m_cache;
};

}
}

#endif // MERE_CACHE_SOFTLINKCACHE_H
