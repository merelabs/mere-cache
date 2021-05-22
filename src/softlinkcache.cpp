#include "softlinkcache.h"
#include "policy/lrucache.h"

#include "mere/utils/fileutils.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>

Mere::Cache::SoftLinkCache::~SoftLinkCache()
{
    if (m_cache)
    {
        delete m_cache;
        m_cache = nullptr;
    }
}

Mere::Cache::SoftLinkCache::SoftLinkCache()
    : SoftLinkCache("/tmp/mere/cache/>>>/")
{
}

Mere::Cache::SoftLinkCache::SoftLinkCache(const std::string &path)
    : Mere::Cache::LinkCache(path),
      m_cache(new Policy::LRUCache(100))
{
}

bool Mere::Cache::SoftLinkCache::has(const std::string &key)
{
    if (key.empty()) return false;

    if (m_cache && m_cache->has(key))
        return false;

    std::string path(this->path());
    path.append(key);
    return Mere::Utils::FileUtils::isExist(path);
}

std::string Mere::Cache::SoftLinkCache::get(const std::string &key, bool *flag)
{
    if (key.empty())
    {
        if (flag) *flag = false;
        return "";
    }

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

    if (m_cache)
    {
        m_cache->set(key, value);
    }

    return value;
}

void Mere::Cache::SoftLinkCache::set(const std::string &key, const std::string &value, bool *flag)
{
    if (key.empty())
    {
        if (flag) *flag = false;
        return;
    }

    auto pos = key.find("/");
    if (pos != std::string::npos) return;

    if (value.empty())
    {
        std::string path(this->path());
        path.append(key);

        Mere::Utils::FileUtils::remove(path);

        return;
    }

    // set it
    if(m_cache)
    {
        m_cache->set(key, value);
    }

    std::string path(this->path());
    symlink(value.c_str(), path.append(key).c_str());
}

//void Mere::Cache::SoftLinkCache::setPolicy(Cache *cache)
//{
//    m_cache = cache;
//}
