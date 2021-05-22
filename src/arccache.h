#ifndef MERE_CACHE_ARCCACHE_H
#define MERE_CACHE_ARCCACHE_H

#include "global.h"
#include "cache.h"

namespace Mere
{
namespace Cache
{

class MERE_CACHE_LIB_SPEC ARCCache : public Mere::Cache::Cache
{
public:
    ~ARCCache();
    explicit ARCCache(int capacity);

private:
    int m_capacity;
};

}
}

#endif // MERE_CACHE_ARCCACHE_H
