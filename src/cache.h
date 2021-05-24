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
    explicit Cache(std::size_t capacity);

    std::size_t capacity() const;

    virtual bool has(const std::string &key) = 0;
    virtual std::string get(const std::string &key, bool *flag = nullptr) = 0;
    virtual void set(const std::string &key, const std::string &value, bool *flag = nullptr) = 0;

    virtual void evict() = 0;

private:
    std::size_t m_capacity;


};
}
}

#endif // MERE_CACHE_CACHE_H
