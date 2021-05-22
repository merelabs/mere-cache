#ifndef MERE_CACHE_LINKCACHE_H
#define MERE_CACHE_LINKCACHE_H

#include "global.h"
#include "cache.h"

#include <string>

namespace Mere
{
namespace Cache
{

class MERE_CACHE_LIB_SPEC LinkCache : public Cache
{
public:
    virtual ~LinkCache();
    LinkCache(const std::string &path);

    std::string path();
    void path(const std::string &path);
private:
    std::string m_path;
};
}
}

#endif // MERE_CACHE_LINKCACHE_H
