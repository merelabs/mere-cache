#ifndef MERE_CACHE_MFUCACHE_H
#define MERE_CACHE_MFUCACHE_H

namespace Mere
{
namespace Cache
{
namespace Policy
{

class MFUCache
{
public:
    ~MFUCache();
    explicit MFUCache(int capacity);
private:
    int m_capacity;
};

}
}
}

#endif // MERE_CACHE_MFUCACHE_H
