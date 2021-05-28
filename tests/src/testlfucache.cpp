#include "testlfucache.h"
#include "mere/cache/lfucache.hpp"

void TestLFUCache::initTestCase()
{
}

void TestLFUCache::cleanupTestCase()
{
}

void TestLFUCache::testset()
{
    Mere::Cache::LFUCache<std::string, std::string> cache(2);
    cache.set("a", "A");
    QVERIFY(cache.get("a").compare("A") == 0);

    bool set;
    QVERIFY(cache.get("a", &set).compare("A") == 0);
    QVERIFY(set);
}

void TestLFUCache::testevict()
{
    Mere::Cache::LFUCache<std::string, std::string> cache(2);
    cache.set("a", "A");
    cache.set("b", "B");

    cache.get("a");
    cache.get("a");
    cache.get("b");

    cache.set("c", "C");

    bool set;
    QVERIFY(cache.get("a", &set).compare("A") == 0);
    QVERIFY(set);

    QVERIFY(cache.get("b", &set).compare("") == 0);
    QVERIFY(!set);
}
