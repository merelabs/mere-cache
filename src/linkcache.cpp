#include "linkcache.h"
#include "mere/utils/pathutils.h"

Mere::Cache::LinkCache::~LinkCache()
{
}

Mere::Cache::LinkCache::LinkCache(const std::string &path)
    : m_path(path)
{
}

std::string Mere::Cache::LinkCache::path()
{
    return m_path;
}

void Mere::Cache::LinkCache::path(const std::string &path)
{
    m_path = path;
    if(m_path.back() != '/') m_path.append("/");
    Mere::Utils::PathUtils::create_if_none(m_path, 0777);
}

