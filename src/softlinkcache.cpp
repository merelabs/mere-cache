#include "softlinkcache.h"
#include "lrucache.h"

#include "mere/utils/fileutils.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>

Mere::Cache::SoftLinkCache::~SoftLinkCache()
{
}

Mere::Cache::SoftLinkCache::SoftLinkCache()
    : SoftLinkCache("/tmp/mere/cache/>>>/")
{
}

Mere::Cache::SoftLinkCache::SoftLinkCache(const std::string &path)
    : Mere::Cache::DiskCache(path),
      m_cache(nullptr)
{
}

std::string Mere::Cache::SoftLinkCache::get(const std::string &key, bool *flag)
{
    if (m_cache)
    {
        bool _flag;
        std::string path = m_cache->get(key, &_flag);
        if (_flag)
        {
            if (flag) *flag = true;
            return path;
        }
    }

    std::string path(this->path());
    path.append(key);
    if(!Mere::Utils::FileUtils::isExist(path))
    {
        if (flag) *flag = false;
        return "";
    }

    char link[4096]; /* maxsize of path - 4096 ? */
    int bytes = readlink(path.c_str(), link, sizeof(link));
    if (!bytes)
    {
        if (flag) *flag = false;
        return "";
    }
    link[bytes] = '\0';

    std::string value(link);

    if (m_cache) m_cache->set(key, value);

    return value;
}

void Mere::Cache::SoftLinkCache::set(const std::string &key, const std::string &link)
{
    if (key.empty()) return;

    auto pos = key.find("/");
    if (pos != std::string::npos) return;

    if (link.empty())
    {
        std::string path(this->path());
        path.append(key);

        Mere::Utils::FileUtils::remove(path);

        return;
    }

    // set it
    if(m_cache) m_cache->set(key, link);

    std::string path(this->path());
    symlink(link.c_str(), path.append(key).c_str());
}

void Mere::Cache::SoftLinkCache::setCache(LRUCache *cache)
{
    m_cache = cache;
}
