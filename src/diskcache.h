#ifndef MERE_CACHE_DISKCACHE_H
#define MERE_CACHE_DISKCACHE_H

#include "cache.h"

namespace Mere
{
namespace Cache
{

class DiskCache : public Cache
{
public:
    virtual ~DiskCache();
    explicit DiskCache(const std::string &path);

    std::string path();
    void path(const std::string &path);

private:
    std::string m_path;
};
}
}

#endif // MERE_CACHE_DISKCACHE_H
