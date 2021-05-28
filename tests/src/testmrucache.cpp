#include "testmrucache.h"
#include "mere/cache/mrucache.hpp"

void TestMRUCache::initTestCase()
{
}

void TestMRUCache::cleanupTestCase()
{
}

void TestMRUCache::testset()
{
    Mere::Cache::MRUCache<std::string, std::string> cache(2);
    cache.set("a", "A");

    QVERIFY(cache.get("a").compare("A") == 0);
    bool set;
    QVERIFY(cache.get("a", &set).compare("A") == 0);
    QVERIFY(set);
}

void TestMRUCache::testevict()
{
    Mere::Cache::MRUCache<std::string, std::string> cache(2);
    cache.set("a", "A");

    bool set;
    QVERIFY(cache.get("a", &set).compare("A") == 0);
    QVERIFY(set);

    cache.set("b", "B");
    cache.set("c", "C");

    QVERIFY(cache.get("b", &set).compare("") == 0);
    QVERIFY(!set);
}
