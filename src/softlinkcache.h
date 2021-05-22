#ifndef MERE_CACHE_SOFTLINKCACHE_H
#define MERE_CACHE_SOFTLINKCACHE_H

#include "global.h"
#include "cache.h"

#include "linkcache.h"
#include <map>

namespace Mere
{
namespace Cache
{

class MERE_CACHE_LIB_SPEC SoftLinkCache : public LinkCache
{
public:
    virtual ~SoftLinkCache();
    SoftLinkCache();
    explicit SoftLinkCache(const std::string &path);

    bool has(const std::string &key) override;
    std::string get(const std::string &key, bool *flag = nullptr) override;
    void set(const std::string &key, const std::string &value, bool *flag = nullptr) override;
    void evict() override;

//    void setPolicy(Cache *cache);

private:
    Cache *m_cache;
};

}
}

#endif // MERE_CACHE_SOFTLINKCACHE_H
