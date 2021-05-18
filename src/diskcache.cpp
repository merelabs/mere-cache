#include "diskcache.h"
#include "mere/utils/pathutils.h"

Mere::Cache::DiskCache::~DiskCache()
{
}

Mere::Cache::DiskCache::DiskCache(const std::string &path)
    : m_path(path)
{
}

std::string Mere::Cache::DiskCache::path()
{
    return m_path;
}

void Mere::Cache::DiskCache::path(const std::string &path)
{
    m_path = path;
    if(m_path.back() != '/') m_path.append("/");
    Mere::Utils::PathUtils::create_if_none(m_path, 0777);
}

