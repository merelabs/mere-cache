#ifndef MERE_CACHE_CACHE_H
#define MERE_CACHE_CACHE_H

#include <string>

namespace Mere
{
namespace Cache
{

template <typename Key, typename Value>
class Cache
{
public:
    virtual ~Cache(){};
    explicit Cache(std::size_t capacity)
        : m_capacity(capacity)
    {

    }

    std::size_t capacity() const
    {
        return m_capacity;
    }

    virtual bool has(const Key &key) = 0;
    virtual Value get(const Key &key, bool *flag = nullptr) = 0;
    virtual void set(const Key &key, const Value &value, bool *flag = nullptr) = 0;
    virtual void evict() = 0;

private:
    std::size_t m_capacity;
};
}
}

#endif // MERE_CACHE_CACHE_H
