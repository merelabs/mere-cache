#include "cache.h"

Mere::Cache::Cache::~Cache()
{

}

Mere::Cache::Cache::Cache(std::size_t capacity)
    : m_capacity(capacity)
{

}

std::size_t Mere::Cache::Cache::capacity() const
{
    return m_capacity;
}
