#ifndef MERE_CACHE_CACHE_H
#define MERE_CACHE_CACHE_H

#include <string>

namespace Mere
{
namespace Cache
{

class Cache
{
public:
    virtual ~Cache();
    explicit Cache();

    virtual bool has(const std::string &key) = 0;
    virtual std::string get(const std::string &key, bool *flag = nullptr) = 0;
    virtual void set(const std::string &key, const std::string &value, bool *flag = nullptr) = 0;

    virtual void evict() = 0;
};
}
}

#endif // MERE_CACHE_CACHE_H
